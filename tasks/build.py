####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the Alpine Toolkit software.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# $ALPINE_TOOLKIT_END_LICENSE$
#
####################################################################################################

####################################################################################################

from pathlib import Path
import glob
import os
import pathlib
import tempfile
import shutil
import sys

import invoke
from invoke import task, call

import yaml

# https://github.com/tartley/colorama
from colorama import init, Fore
from termcolor import colored
# use Colorama to make Termcolor work on Windows too
init(autoreset=True)

from .lib.build import git_clone, download, untar, unzip

####################################################################################################

def print_colored(message: str, color: str) -> None:
    print(colored(message, color))

def print_error(message: str) -> None:
    print_colored(message, 'red')

def print_section(message: str) -> None:
    print_colored(message, 'blue')

def print_info(message: str) -> None:
    print_colored(message, 'green')

def print_section_rule() -> None:
    print_colored('─'*100, 'blue')

####################################################################################################

def _init_config(ctx) -> None:
    if hasattr(ctx.build, 'source_path'):
        return

    ctx.build['source'] = Path(__file__).parents[1]

    if not hasattr(ctx.build, 'qt'):
        config_files = glob.glob(str(ctx.build.source.joinpath('build-config', '*.yaml')))
        print_error("Usage: inv -f build-XXX.yaml build.XXX")
        print("Available config files:")
        for _ in config_files:
            _ = Path(_).relative_to(ctx.build.source)
            print(' '*4, _)
        sys.exit(1)
        # raise NameError("Config file is missing")

    ctx.build['resources_path'] = ctx.build.source.joinpath('resources')

    if hasattr(ctx.build, 'path'):
        ctx.build.path = Path(ctx.build.path)
    else:
        ctx.build['path'] = ctx.build.source.joinpath(f'build-{ctx.build.arch}')

    ctx.build['third_parties'] = ctx.build.source.joinpath('third-parties')
    # ctx.build['openssl_source'] = ctx.build.third_parties.joinpath('openssl', 'openssl-source')

    ARCH = (
        'gcc_64',
        'android_x86',
        'android_x86_64',
        'android_armv7',
        'android_arm64_v8a',
    )
    if ctx.build.arch not in ARCH:
        raise NameError(f"arch must be {ARCH}")

    _set_qt(ctx)

    for _ in ('CFLAGS', 'CXXFLAGS'):
        os.environ.pop(_, None)

####################################################################################################

# def _set_qt(ctx, qt_path=None, arch='gcc_64'):
#     if qt_path is None:
#         qt_path = os.getenv('QT_PATH')
#     if qt_path is None:
#         raise NameError('The "QT_PATH" environment variable must be set to Qt path')
#     ctx.qt_path = Path(qt_path)

def _set_qt(ctx) -> None:
    ctx.build.qt = Path(ctx.build.qt)
    if not ctx.build.qt.exists():
        raise NameError("Qt not found {ctx.build.qt}")
    match sys.platform:
        case 'linux':
            host_arch = 'gcc_64'
            ctx.build['qt_host_path'] = ctx.build.qt.joinpath(host_arch)
            ctx.build['qt_bin_path'] = ctx.build.qt_host_path.joinpath('bin')
            ctx.build['qt_lib_path'] = ctx.build.qt_host_path.joinpath('lib')
            ctx.build['qt_arch_path'] = ctx.build.qt.joinpath(ctx.build.arch)
            ctx.build['qmake_path'] = ctx.build.qt_arch_path.joinpath('bin', 'qmake')
        case 'darwin':
            raise NotImplementedError
        case 'win32':
            raise NotImplementedError

####################################################################################################

@task()
def show_config(ctx):
    _init_config(ctx)

    config = dict(ctx.config.items())

    def path_representer(dumper, data):
        return dumper.represent_scalar('!PATH', str(data))

    yaml.add_representer(pathlib.PosixPath, path_representer)

    print(yaml.dump(config))

####################################################################################################

@task
def install_qt(ctx):
    print('Download Qt installer https://www.qt.io/download-qt-installer')
    # https://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run.mirrorlist
    qt_installer_url = 'https://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run'
    qt_installer_path = Path('qt_installer')
    download(qt_installer_url, qt_installer_path, executable=True)

####################################################################################################

@task
def install_android_sdk(ctx):
    # https://doc.qt.io/qt-6/android-getting-started.html
    # https://developer.android.com/studio
    # https://dl.google.com/android/repository
    commandlinetools_url = 'https://dl.google.com/android/repository/commandlinetools-linux-8512546_latest.zip'

    # sdkmanager --sdk_root=<ANDROID_SDK_ROOT> --install "cmdline-tools;latest" "platform-tools" "platforms;android-31" "build-tools;31.0.0" "ndk;22.1.7171670"
    # sdkmanager --sdk_root=<ANDROID_SDK_ROOT> --install "emulator" "patcher;v4"

####################################################################################################

@task()
def show_android(ctx):
    _init_config(ctx)

    sdk = Path(ctx.build.sdk)
    ndk = Path(ctx.build.ndk)
    print(f'SDK {sdk}')

    sdkmanager = sdk.joinpath('cmdline-tools', 'latest', 'bin', 'sdkmanager')
    ctx.run(f'{sdkmanager} --list_installed', echo=True)

    with open(ndk.joinpath('source.properties')) as fh:
        for line in fh.readlines():
            if line.startswith('Pkg.Revision ='):
                ndk_revision = line.split('=')[1].strip()
                print(f'NDK {ndk_revision}   {ndk}')

####################################################################################################

@task()
def generate_code(ctx):
    _init_config(ctx)
    with ctx.cd(ctx.build.source.joinpath('code-generator')):
        ctx.run('generate-all')
    # shaders are managed by CMakeLists

####################################################################################################

@task()
def generate_icons(ctx):
    _init_config(ctx)
    icons_directory = ctx.build.resources_path.joinpath('icons')
    svg_directory = ctx.build.resources_path.joinpath('icon-resources', 'svg')
    png_directory = svg_directory.joinpath('png')
    print_info(f'SVG path: {svg_directory}')
    print_info(f'PNG path: {png_directory}')
    if not png_directory.exists():
        png_directory.mkdir()
    for svg_path in svg_directory.glob('*.svg'):
        svg_path = Path(svg_path)
        png_path = png_directory.joinpath(f'{svg_path.stem}-black.png')
        png3_path = png_directory.joinpath(f'{svg_path.stem}-black@3x.png')
        # png3_path = str(png_path).replace('.png', '@3x.png')
        if not png_path.exists():
            print_section(f'Generate {png_path.name}', 'blue')
            options = '--export-area-page --export-background=white --export-background-opacity=0'
            # Warning: Option --export-png= is deprecated
            ctx.run(f'inkscape --export-png={png_path} {options} --export-width=24 --export-height=24 {svg_path}')
            ctx.run(f'inkscape --export-png={png3_path} {options} --export-width=72 --export-height=72 {svg_path}')
        for path in (png_path, png3_path):
            link = icons_directory.joinpath(path.name)
            if not link.exists():
                target = Path('..', 'icon-resources', 'svg', 'png', path.name)
                link.symlink_to(target)

####################################################################################################

@task()
def generate_tones(ctx):
    _init_config(ctx)
    from .lib.tones.make_tones import make_tones
    make_tones(ctx)

####################################################################################################

@task(post=[generate_icons, generate_tones])
def init_source(ctx):
    _init_config(ctx)
    print_section_rule()
    print_section("Initialise source ...")

    #########################
    # Code Generator
    def not_source_exists(*args):
        return not ctx.build.source.joinpath(*args).exists()
    if not_source_exists('src', 'data_sources', 'third_party_license', 'third_party_license_schema.h'):
        generate_code(ctx)

    #########################
    # OpenSSL
    openssl_directory = ctx.build.third_parties.joinpath('openssl')
    openssl_source = openssl_directory.joinpath('openssl-source')
    if not openssl_source.exists():
        # if ctx.build.openssl.endswith('.git'):
        url = "https://github.com/openssl/openssl"
        branch = "OpenSSL_1_1_1-stable"
        git_clone(ctx, url, openssl_source, branch=branch)
        # else:
        #     tar_filename = ctx.build.openssl + '.tar.gz'
        #     url = f'https://www.openssl.org/source/{tar_filename}'
        #     tar_path = ctx.build.third_parties.joinpath(tar_filename)
        #     download(url, tar_path)
        #     untar(tar_path, ctx.build.third_parties)

    #########################
    # CMark (in Qt6)
    # ../camptocamp/camptocamp_document.cpp:38:10: erreur fatale: cmark/cmark.h : Aucun fichier ou dossier de ce type
    #    38 | #include "cmark/cmark.h"
    # ./third-parties/include/cmark/cmark.h
    #
    # cmark_source = ctx.build.third_parties.joinpath('cmark', 'cmark-source')
    # if not cmark_source.joinpath('src').exists():
    #     cmark_url = 'https://github.com/github/cmark'
    #     git_clone(ctx, cmark_url, cmark_source)

    #########################
    # Snowball
    snowball_dirctory = ctx.build.third_parties.joinpath('snowball')
    snowball_source = snowball_dirctory.joinpath('snowball-source')
    if not snowball_source.joinpath('src_c').exists():
        raise NameError("Snowball source are missing")
        # url = 'https://github.com/snowballstem/snowball'
        # Fixme: snowball is not up to date
        # git_clone(ctx, url, snowball_source)
        # third-parties/include/snowball
        # libstemmer.h -> ../../snowball/snowball-source/include/libstemmer.h

    #########################
    # SQLite
    sqlite_directory = ctx.build.third_parties.joinpath('sqlite')
    sqlite_amalgamation_source = sqlite_directory.joinpath('sqlite-amalgamation')
    if not sqlite_amalgamation_source.exists():
        version = '3380500'
        url_base = "https://www.sqlite.org/2022"
        url = f"{url_base}/sqlite-amalgamation-{version}.zip"
        # url = f"{url_base}/sqlite-src-{version}.zip"
        zip_path = sqlite_directory.joinpath('sqlite-amalgamation.zip')
        download(url, zip_path)
        print_info(f"  Unzip {zip_path} ...")
        unzip(zip_path, sqlite_directory)
        sqlite_amalgamation_source.symlink_to(f'sqlite-amalgamation-{version}')
        zip_path.unlink()

    #########################
    # Proj
    proj_directory = ctx.build.third_parties.joinpath('proj')
    proj_source = proj_directory.joinpath('proj-source')
    if not proj_source.exists():
        version = '9.0.0'
        data_version = '1.9'
        url_base = 'https://download.osgeo.org/proj'
        tar_filename = f'proj-{version}.tar.gz'
        tar_data_filename = f'proj-data-{data_version}.tar.gz'
        tar_url = f'{url_base}/{tar_filename}'
        tar_data_url = f'{url_base}/{tar_data_filename}'
        git_url = 'https://github.com/OSGeo/Proj'
        git_data_url = 'https://github.com/OSGeo/PROJ-data'   # contains the cloud-optimized GeoTIFF files
        # git_clone(ctx, proj_url, proj_source)
        tar_path = proj_directory.joinpath(tar_filename)
        tar_data_path = proj_directory.joinpath(tar_data_filename)
        download(tar_url, tar_path)
        untar(tar_path, proj_directory)
        proj_source.symlink_to(f'proj-{version}')
        tar_path.unlink()
        # download(tar_data_url, tar_data_path) # 563 MB
        with ctx.cd(proj_source):
            ctx.run('patch -p1 -i patch.diff')

    #########################
    # libiconv
    #  https://www.gnu.org/software/libiconv

    libiconv_directory = ctx.build.third_parties.joinpath('libiconv')
    libiconv_source = libiconv_directory.joinpath('libiconv-source')
    if not libiconv_source.exists():
        version = '1.17'
        url_base = 'https://ftp.gnu.org/pub/gnu/libiconv'
        tar_filename = f'libiconv-{version}.tar.gz'
        tar_url = f'{url_base}/{tar_filename}'
        tar_path = libiconv_directory.joinpath(tar_filename)
        download(tar_url, tar_path)
        untar(tar_path, libiconv_directory)
        libiconv_source.symlink_to(f'libiconv-{version}')
        tar_path.unlink()

    #########################
    # geos
    #  https://libgeos.org

    geos_directory = ctx.build.third_parties.joinpath('geos')
    geos_source = geos_directory.joinpath('geos-source')
    if not geos_source.exists():
        version = '3.10.3'
        url_base = 'http://download.osgeo.org/geos'
        tar_filename = f'geos-{version}.tar.bz2'
        tar_url = f'{url_base}/{tar_filename}'
        tar_path = geos_directory.joinpath(tar_filename)
        download(tar_url, tar_path)
        untar(tar_path, geos_directory)
        geos_source.symlink_to(f'geos-{version}')
        tar_path.unlink()

    #########################
    # Spatialite

    spatialite_directory = ctx.build.third_parties.joinpath('spatialite')
    spatialite_source = spatialite_directory.joinpath('spatialite-source')
    if not spatialite_source.exists():
        version = '5.0.1'
        url_base = 'https://www.gaia-gis.it/gaia-sins'
        tar_filename = f'libspatialite-{version}.tar.gz'
        tar_url = f'{url_base}/{tar_filename}'
        # git_clone(ctx, spatialite_url, spatialite_source)
        tar_path = spatialite_directory.joinpath(tar_filename)
        download(tar_url, tar_path)
        untar(tar_path, spatialite_directory)
        spatialite_source.symlink_to(f'libspatialite-{version}')
        tar_path.unlink()

    # git_url = 'https://github.com/libspatialindex/libspatialindex-source'

    #########################
    # C2C Login

    camptocamp_login = ctx.build.source.joinpath('unit-tests', 'camptocamp', 'login.h')
    if not camptocamp_login.exists():
        with open(camptocamp_login, 'w', encoding='utf8') as fh:
            data = [
                'QString username = "...";'
                'QString password = "...";'
            ]
            fh.write(os.linesep.join(data))
        raise NameError(f"Created a template for {camptocamp_login}")

####################################################################################################

@task()
def linguist(ctx):
    ts_path = ctx.build.source.joinpath('translations', 'alpine-toolkit.fr_FR.ts')
    ctx.run(f'linguist {ts_path}')

####################################################################################################

@task()
def qml(ctx, path):
    _init_config(ctx)

    path = Path(path)
    if not (path.exists() and path.is_dir()):
        print_error(f"Directory {path} doesn't exist")
    qml_path = ctx.build.qt_bin_path.joinpath('qml')
    main_qml = 'main.qml'
    includes = ' '.join([f'-I {_}' for _ in ('qml',)])
    command = f'{qml_path} {includes} {main_qml}'
    env = {}
    with ctx.cd(path):
        ctx.run(command, env=env)

####################################################################################################

@task(
    pre=[init_source],
    optional=[],
)
def build(
        ctx,
        wipe=False,
        cmake=True,
        clean=False,
        make=True,
        deploy=False,
        verbose=True,
):
    print_section_rule()
    _init_config(ctx)
    is_android = ctx.build.arch.startswith('android')
    use_ninja = ctx.build.generator == 'ninja'

    env = {
        'LC_ALL': 'C',
    }

    print_info(f"Source path: {ctx.build.source}")
    print_info(f"Build path: {ctx.build.path}")
    print_info(f'Qt path: {ctx.build.qt}')
    print_info(f"Arch: {ctx.build.arch}")
    print_info(f"Build type: {ctx.build.build_type}")
    print_info(f"CFLAGS: {ctx.build.cflags}")
    if is_android:
        print_info(f"NDK path: {ctx.build.ndk}")
        print_info(f"SDK path: {ctx.build.sdk}")

    if wipe:
        print_section(f'Wipe {ctx.build.path}')
        shutil.rmtree(ctx.build.path)

    if not ctx.build.path.exists():
        ctx.build.path.mkdir()

    with ctx.cd(ctx.build.path):

        if clean:
            for _ in (
                    'CMakeCache.txt',
                    'compile_commands.json',
            ):
                _ = Path(_)
                if _.exists():
                    _.unlink()
            ctx.run(f'cmake --build {ctx.build.path} --target clean')

        if cmake:
            # /etc/security/limits.d/00-user.conf

            command = [
                'cmake',
                f'-S {ctx.build.source}',
                f'-B {ctx.build.path}',

                '-G Ninja' if use_ninja else '',
                # -D CMAKE_GENERATOR:STRING=Ninja

                f'-D CMAKE_BUILD_TYPE:STRING={ctx.build.build_type}',

                f'-D CMAKE_PREFIX_PATH:PATH={ctx.build.qt_arch_path}',
                f'-D CMAKE_FIND_ROOT_PATH:PATH={ctx.build.qt_arch_path}',

                f'-D CMAKE_C_FLAGS:STRING="{ctx.build.cflags}"',
                f'-D CMAKE_CXX_FLAGS:STRING="{ctx.build.cflags}"',

                f'-D QT_HOST_PATH:PATH={ctx.build.qt_host_path}',
            ]

            # -DCMAKE_PROJECT_INCLUDE_BEFORE:FILEPATH=/srv/qt/Qt/Tools/QtCreator/share/qtcreator/package-manager/auto-setup.cmake

            if verbose:
                # cf. main CMakeLists.txt
                command.append("-D CMAKE_VERBOSE_MAKEFILE:BOOL=ON")

            if is_android:
                # https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#cross-compiling-for-android
                # https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html
                ndk = Path(ctx.build.ndk)
                sdk = Path(ctx.build.sdk)
                toolchain_path = ndk.joinpath('toolchains', 'llvm', 'prebuilt', 'linux-x86_64', 'bin')
                cmake_toolchain_path = ndk.joinpath('build', 'cmake', 'android.toolchain.cmake')
                clang_path = toolchain_path.joinpath('clang')
                ABI_MAP = {
                    'android_armv7': 'armeabi-v7a',
                    'android_x86': 'x86',
                }
                abi = ABI_MAP[ctx.build.arch]
                command += [
                    # This variable is specified on the command line when cross-compiling with
                    # CMake. It is the path to a file which is read early in the CMake run and which
                    # specifies locations for compilers and toolchain utilities, and other target
                    # platform and compiler related information.
                    # https://cmake.org/cmake/help/latest/variable/CMAKE_TOOLCHAIN_FILE.html
                    f'-D CMAKE_TOOLCHAIN_FILE:FILEPATH={cmake_toolchain_path}',

                    # Done
                    #   Must be specified to enable cross compiling for Android.
                    #   https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_NAME.html#variable:CMAKE_SYSTEM_NAME
                    #   '-DCMAKE_SYSTEM_NAME=Android',
                    #   Set to the Android API level
                    #   https://cmake.org/cmake/help/latest/variable/CMAKE_ANDROID_NDK.html#variable:CMAKE_ANDROID_NDK
                    #   f'-D CMAKE_ANDROID_NDK:PATH={ndk}',
                    #   https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_VERSION.html
                    #   '-DCMAKE_SYSTEM_VERSION=...',
                    #   https://cmake.org/cmake/help/latest/variable/CMAKE_ANDROID_ARCH_ABI.html
                    #   '-DCMAKE_ANDROID_ARCH_ABI=x86',

                    f'-D CMAKE_C_COMPILER:FILEPATH={clang_path}',
                    f'-D CMAKE_CXX_COMPILER:FILEPATH={clang_path}++',

                    f'-D ANDROID_NDK:PATH={ndk}',
                    f'-D ANDROID_SDK_ROOT:PATH={sdk}',
                    f'-D ANDROID_ABI:STRING={abi}',
                    '-D ANDROID_NATIVE_API_LEVEL:STRING=23',
                    '-D ANDROID_STL:STRING=c++_shared',

                   '-D QT_NO_GLOBAL_APK_TARGET_PART_OF_ALL:BOOL=ON',
                    f'-D QT_QMAKE_EXECUTABLE:FILEPATH={ctx.build.qmake_path}',
                ]

            command += [
                # https://sarcasm.github.io/notes/dev/compilation-database.html#cmake
                #     This will create a file name compile_commands.json in the build directory.
                '-D CMAKE_EXPORT_COMPILE_COMMANDS:STRING=ON',
            ]

            command += [
                '-D SANITIZE:STRING=OFF',
                '-D INSTRUMENT_FUNTIONS:STRING=OFF',
            ]

            command = ' '.join(command)
            print_section_rule()
            print_section('Run CMake ...')
            print_section(command.replace(' -', os.linesep + '  -'))
            ctx.run(command, echo=True, env=env)

            if not is_android:
                print_section_rule()
                print_section('Run lupdate ...')
                ctx.run(f'cmake --build {ctx.build.path} --target alpine-toolkit_lupdate', echo=True, warn=True)

            if not is_android:
                for _ in ('compile_commands.json', 'config.h'):
                    link = ctx.build.source.joinpath(_)
                    if link.exists():
                        link.unlink()
                    if not link.exists():
                        target = ctx.build.path.joinpath(_)
                        link.symlink_to(target)

        if make:
            print_section_rule()
            print_section('Run Ninja ...')
            # ctx.run('cmake --build {ctx.build.path} --parallel 2 --target all')
            if use_ninja:
                # -C build-cmake
                command = 'ninja -j2'
                if verbose:
                    command += ' -v'
                ctx.run(command)
            else:
                # -k
                ctx.run('make -j4')

        if is_android and deploy:
            print_section_rule()
            command = [
                str(ctx.build.qt_bin_path.joinpath('androiddeployqt')),
                '--input {ctx.build.path}/android-touch-app-deployment-settings.json',
                '--output {ctx.build.path}/android-build',
                f'--android-platform android-{ctx.build.android_api}',
                f'--jdk {ctx.build.jdk}',
                '--gradle',
            ]
            command = ' '.join(command)
            print_section(command)
            ctx.run(command, echo=True)

####################################################################################################

@task(
    pre=[call(build, cmake=False)]
)
def unit_test(ctx):
    # _init_config(ctx)
    unit_test_path = ctx.build.path.joinpath('unit-tests')

    print_section('Run unit tests...')
    tests = []
    failed = []
    for root, _, filenames in os.walk(unit_test_path):
        root = Path(root)
        for filename in filenames:
            filename = root.joinpath(filename)
            if os.access(filename, os.X_OK):   # Fixme: Unix
                filename_part = str(filename).replace(str(ctx.build.path.parent), '.')
                print()
                print_section('='*100)
                print_section(f'Run {filename_part}')
                try:
                    tests.append(filename_part)
                    ctx.run(str(filename))
                except invoke.exceptions.UnexpectedExit:
                    failed.append(filename_part)

    if failed:
        print()
        rule = '!'*100
        print(rule)
        print_error(f'Failures {len(failed)}/{len(tests)}:')
        for _ in failed:
            print_error(' '*4, _)
        print(rule)

    # rm unit_tests_log.txt
    # rm unit_test_failure.txt
    #   ${unit_test} &>> unit_tests_log.txt

####################################################################################################

@task(
    pre=[call(build, cmake=False)]
)
def run(ctx):
    # _init_config(ctx)

    print_section_rule()
    print('Run Environment:')
    _ = yaml.dump(dict(ctx.run_env)).strip()
    print(_)
    print_section_rule()
    command = str(ctx.build.path.joinpath('src', 'alpine-toolkit'))
    ctx.run(command, env=ctx.run_env)

####################################################################################################

# Disabled
# @task(
#     pre=[init_source],
# )
def build_openssl(ctx, clean=False):
    # https://doc-snapshots.qt.io/qt6-dev/android-openssl-support.html
    #
    # https://github.com/KDAB/android_openssl is no longer maintained for Qt6
    #
    # https://doc.qt.io/qt-6/ssl.html
    #
    # See NOTES.ANDROID
    # target are: android-arm android-arm64 / android-x86 android-x86_64
    # export ANDROID_NDK_HOME=/home/whoever/Android/android-sdk/ndk/20.0.5594570
    # PATH=$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin:$ANDROID_NDK_HOME/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin:$PATH
    # ./Configure android-arm64 -D__ANDROID_API__=29
    # make
    _init_config(ctx)
    openssl_build_path = ctx.build.path.joinpath('third-parties', 'openssl')
    if clean:
        shutil.rmtree(openssl_build_path)
    if not openssl_build_path.exists():
        print("Copy OpenSSL source ...")
        ctx.build.path.mkdir(parents=True, exist_ok=True)
        # shutil.copytree(ctx.build.openssl_source, openssl_build_path)
        openssl_build_path.mkdir(parents=True)
    with ctx.cd(openssl_build_path):
        print("Build OpenSSL ...")
        ndk_path = Path(ctx.build.ndk)
        env_path = ':'.join([str(_) for _ in (
            ndk_path.joinpath('toolchains', 'llvm', 'prebuilt', 'linux-x86_64', 'bin'),
            ndk_path.joinpath('toolchains', 'arm-linux-androideabi-4.9', 'prebuilt', 'linux-x86_64', 'bin'),
            os.getenv('PATH'),
        )])
        env = {
            'ANDROID_NDK_HOME': ctx.build.ndk,
            'PATH': env_path,
        }
        ARCH_MAP = {
            'android_armv7': 'android-arm',
            'android_x86': 'android-x86',
        }
        arch = ARCH_MAP[ctx.build.arch]
        command = f"{ctx.build.openssl_source}/Configure shared {arch} -D__ANDROID_API__={ctx.build.android_api}"
        print(env)
        print(command)
        ctx.run(command, env=env)
        # ctx.run('make clean', env=env)
        # ctx.run('make', env=env)
        # build libcrypto and libssl shared libraries that are not versioned, but with an _1_1 suffix
        ctx.run('make SHLIB_VERSION_NUMBER= SHLIB_EXT=_1_1.so', env=env)
        # lib_path = openssl_build_path.joinpath('libssl_1_1.so')

####################################################################################################

@task()
def list_avd(ctx):
    _init_config(ctx)
    avdmanager = Path(ctx.build.sdk).joinpath('cmdline-tools', 'latest', 'bin', 'avdmanager')
    command = f"{avdmanager} list avd"
    ctx.run(command)

####################################################################################################

@task()
def start_emulator(ctx, name):
    _init_config(ctx)
    emulator = Path(ctx.build.sdk).joinpath('emulator', 'emulator')
    command = f"{emulator} @{name}"
    ctx.run(command)
