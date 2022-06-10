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
import os
import pathlib
import sys

import invoke
from invoke import task, call

import yaml

####################################################################################################

def _init_config(ctx) -> None:
    if hasattr(ctx.build, 'source_path'):
        return

    ARCH = (
        'gcc_64',
        'android_x86',
        'android_x86_64',
        'android_armv7',
        'android_arm64_v8a',
    )
    if ctx.build.arch not in ARCH:
        raise NameError(f"arch must be {ARCH}")

    ctx.build['source'] = Path(__file__).parents[1]
    ctx.build['resources_path'] = ctx.build.source.joinpath('resources')
    ctx.build['path'] = ctx.build.source.joinpath(f'build-{ctx.build.arch}')

    _set_qt(ctx)

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
def dump_config(ctx):

    def to_dict(d):
        return {key: value for key, value in d.items()}

    _init_config(ctx)
    config = ctx.config
    config = to_dict(config)

    def path_representer(dumper, data):
        return dumper.represent_scalar('!PATH', str(data))

    yaml.add_representer(pathlib.PosixPath, path_representer)

    print(yaml.dump(config))

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
    print(f'SVG path: {svg_directory}')
    print(f'PNG path: {png_directory}')
    if not png_directory.exists():
        png_directory.mkdir()
    for svg_path in svg_directory.glob('*.svg'):
        svg_path = Path(svg_path)
        png_path = png_directory.joinpath(f'{svg_path.stem}-black.png')
        png3_path = png_directory.joinpath(f'{svg_path.stem}-black@3x.png')
        # png3_path = str(png_path).replace('.png', '@3x.png')
        if not png_path.exists():
            print(f'Generate {png_path.name}')
            options = '--export-area-page --export-background=white --export-background-opacity=0'
            # Warning: Option --export-png= is deprecated
            ctx.run(f'inkscape --export-png={png_path} {options} --export-width=24 --export-height=24 {svg_path}')
            ctx.run(f'inkscape --export-png={png3_path} {options} --export-width=72 --export-height=72 {svg_path}')
        for path in (png_path, png3_path):
            link = icons_directory.joinpath(path)
            if not link.exists():
                link.symlink_to(path)

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
    print("Initialise source ...")

    def not_source_exists(*args):
        return not ctx.build.source.joinpath(*args).exists()

    def git_clone(url, path):
        print(f"Get {url}")
        with ctx.cd(path.parent):
            ctx.run(f"git clone --depth=1 {cmark_url} {path}", echo=True)

    if not_source_exists('src', 'data_sources', 'third_party_license', 'third_party_license_schema.h'):
        generate_code(ctx)

    third_parties = ctx.build.source.joinpath('third-parties')

    # cmark_source = third_parties.joinpath('cmark', 'cmark.git')
    # cmark_url = 'https://github.com/github/cmark'
    # if not cmark_source.joinpath('src').exists():
    #     git_clone(cmark_url, cmark_source)
    #
    #!# ../camptocamp/camptocamp_document.cpp:38:10: erreur fatale: cmark/cmark.h : Aucun fichier ou dossier de ce type
    #!#    38 | #include "cmark/cmark.h"
    #!# ./third-parties/include/cmark/cmark.h

    snowball_source = third_parties.joinpath('snowball', 'snowball.git')
    if not snowball_source.joinpath('src_c').exists():
        raise NameError("Snowball source are missing")
        snowball_url = 'https://github.com/snowballstem/snowball'
        # Fixme: snowball is not up to date
        # git_clone(snowball_url, snowball_source)
        # third-parties/include/snowball
        # libstemmer.h -> ../../snowball/snowball.git/include/libstemmer.h

    # https://github.com/OSGeo/proj.4.git
    # https://github.com/libspatialindex/libspatialindex.git

    camptocamp_login = ctx.build.source.joinpath('unit-tests', 'camptocamp', 'login.h')
    if not camptocamp_login.exists():
        with open(camptocamp_login, 'w') as fh:
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
        print(f"Directory {path} doesn't exist")
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
        cmake=True,
        clean=False,
        make=True,
        deploy=False,
):
    _init_config(ctx)
    is_android = ctx.build.arch.startswith('android')
    use_ninja = ctx.build.generator == 'ninja'

    env = {
        'LC_ALL': 'C',
        'CFLAGS': ctx.build.cflags,
        'CXXFLAGS': ctx.build.cflags,
        # 'CMAKE_PREFIX_PATH': str(ctx.build.qt_lib_path.joinpath('cmake'))
    }

    print()
    print(f"Source path: {ctx.build.source}")
    print(f"Build path: {ctx.build.path}")
    print(f'Qt path: {ctx.build.qt}')
    print(f"Arch: {ctx.build.arch}")
    print(f"Build type: {ctx.build.build_type}")
    # print(f"Env: {env}")
    print(f"CXXFLAGS: {env['CXXFLAGS']}")
    if is_android:
        print(f"NDK path: {ctx.build.ndk}")
        print(f"SDK path: {ctx.build.sdk}")
    print()

    if not ctx.build.path.exists():
        ctx.build.path.mkdir()

    with ctx.cd(ctx.build.path):

        if clean:
            for _ in (
                    'CMakeCache.txt',
                    'compile_commands.json',
            ):
                os.unlink(_)
            ctx.run('cmake --build {ctx.build.path} --target clean')
            # if Path('Makefile').exists():
            #     ctx.run('make clean')

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
                f'-D QT_HOST_PATH:PATH={ctx.build.qt_host_path}',
            ]

            # -DCMAKE_PROJECT_INCLUDE_BEFORE:FILEPATH=/srv/qt/Qt/Tools/QtCreator/share/qtcreator/package-manager/auto-setup.cmake

            if is_android:
                ndk = Path(ctx.build.ndk)
                sdk = Path(ctx.build.sdk)
                toolchain_path = ndk.joinpath('toolchains', 'llvm', 'prebuilt', 'linux-x86_64', 'bin')
                cmake_toolchain_path = ndk.joinpath('build', 'cmake', 'android.toolchain.cmake')
                clang_path = toolchain_path.joinpath('clang')
                command += [
                    f'-D ANDROID_NDK:PATH={ndk}',
                    f'-D ANDROID_SDK_ROOT:PATH={sdk}',
                    f'-D ANDROID_ABI:STRING=armeabi-v7a',
                    f'-D ANDROID_NATIVE_API_LEVEL:STRING=23',
                    f'-D ANDROID_STL:STRING=c++_shared',
                    f'-D CMAKE_C_COMPILER:FILEPATH={clang_path}',
                    f'-D CMAKE_CXX_COMPILER:FILEPATH={clang_path}++',
                    f'-D CMAKE_TOOLCHAIN_FILE:FILEPATH={cmake_toolchain_path}',
                    f'-D QT_NO_GLOBAL_APK_TARGET_PART_OF_ALL:BOOL=ON',
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
            print(command)
            ctx.run(command, echo=True, env=env)
            ctx.run(f'cmake --build {ctx.build.path} --target alpine-toolkit_lupdate', echo=True)

            for _ in ('compile_commands.json', 'config.h'):
                target = ctx.build.source.joinpath(_)
                if not target.exists():
                    source = ctx.build.path.joinpath(_)
                    source.symlink_to(target)

        if make:
            # ctx.run('cmake --build {ctx.build.path} --parallel 2 --target all')
            if use_ninja:
                # -C build-cmake
                ctx.run('ninja -j2')
            else:
                # -k
                ctx.run('make -j4')

        if is_android and deploy:
            command = [
                str(ctx.build.qt_bin_path.joinpath('androiddeployqt')),
                '--input {ctx.build.path}/android-touch-app-deployment-settings.json',
                '--output {ctx.build.path}/android-build',
                f'--android-platform {ctx.build.android_plaform}',
                f'--jdk {ctx.build.jdk}',
                '--gradle',
            ]
            command = ' '.join(command)
            print(command)
            ctx.run(command, echo=True)

####################################################################################################

@task(
    pre=[call(build, cmake=False)]
)
def unit_test(ctx):
    # _init_config(ctx)
    unit_test_path = ctx.build.path.joinpath('unit-tests')

    print('Run unit tests...')
    tests = []
    failed = []
    for root, _, filenames in os.walk(unit_test_path):
        root = Path(root)
        for filename in filenames:
            filename = root.joinpath(filename)
            if os.access(filename, os.X_OK):   # Fixme: Unix
                filename_part = str(filename).replace(str(ctx.build.path.parent), '.')
                print()
                print('='*100)
                print(f'Run {filename_part}')
                try:
                    tests.append(filename_part)
                    ctx.run(str(filename))
                except invoke.exceptions.UnexpectedExit:
                    failed.append(filename_part)

    if failed:
        print()
        rule = '!'*100
        print(rule)
        print(f'Failures {len(failed)}/{len(tests)}:')
        for _ in failed:
            print(' '*4, _)
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

    print()
    rule = '='*100
    print(rule)
    print('Run Environment:')
    _ = yaml.dump(dict(ctx.run_env)).strip()
    print(_)
    print(rule)
    command = str(ctx.build.path.joinpath('src', 'alpine-toolkit'))
    ctx.run(command, env=ctx.run_env)
