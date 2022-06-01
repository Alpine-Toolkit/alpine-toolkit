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
import sys

import invoke
from invoke import task, call

####################################################################################################

def _set_source_path(ctx):
    if not hasattr(ctx, 'source_path'):
        ctx.source_path = Path(__file__).parents[1]
        ctx.resources_path = ctx.source_path.joinpath('resources')

####################################################################################################

def _set_qt(ctx, qt_path=None, arch='gcc_64'):
    if qt_path is None:
        qt_path = os.getenv('QT_PATH')
    if qt_path is None:
        raise NameError('The "QT_PATH" environment variable must be set to Qt path')

    ctx.qt_path = Path(qt_path)
    match sys.platform:
        case 'linux':
            host_arch = 'gcc_64'
            ctx.qt_host_path = ctx.qt_path.joinpath(host_arch)
            ctx.qt_path_bin = ctx.qt_host_path.joinpath('bin')
            ctx.qt_path_lib = ctx.qt_host_path.joinpath('lib')
            ctx.qt_arch_path = ctx.qt_path.joinpath(arch)
            ctx.qmake_path = ctx.qt_arch_path.joinpath('bin', 'qmake')
        case 'darwin':
            raise NotImplementedError
        case 'win32':
            raise NotImplementedError

####################################################################################################

@task()
def generate_code(ctx):
    _set_source_path(ctx)
    with ctx.cd(ctx.source_path.joinpath('code-generator')):
        ctx.run('generate-all', pty=True)
    # shaders are managed by CMakeLists

####################################################################################################

@task()
def generate_icons(ctx):
    _set_source_path(ctx)
    icons_directory = ctx.resources_path.joinpath('icons')
    svg_directory = ctx.resources_path.joinpath('icon-resources', 'svg')
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
    _set_source_path(ctx)
    from .lib.tones.make_tones import make_tones
    make_tones(ctx)

####################################################################################################

@task(post=[generate_icons, generate_tones])
def init_source(ctx):
    _set_source_path(ctx)
    print("Initialise source ...")

    def not_source_exists(*args):
        return not ctx.source_path.joinpath(*args).exists()

    def git_clone(url, path):
        print(f"Get {url}")
        with ctx.cd(path.parent):
            ctx.run(f"git clone --depth=1 {cmark_url} {path}", echo=True)

    if not_source_exists('src', 'third_party_license', 'third_party_license_schema.h'):
        generate_code(ctx)

    third_parties = ctx.source_path.joinpath('third-parties')

    # cmark_source = third_parties.joinpath('cmark', 'cmark.git')
    # cmark_url = 'https://github.com/github/cmark'
    # if not cmark_source.joinpath('src').exists():
    #     git_clone(cmark_url, cmark_source)

    snowball_source = third_parties.joinpath('snowball', 'snowball.git')
    snowball_url = 'https://github.com/snowballstem/snowball'
    if not snowball_source.joinpath('src_c').exists():
        raise NameError("Snowball source are missing")
        # Fixme: snowball is not up to date
        # git_clone(snowball_url, snowball_source)
        # third-parties/include/snowball
        # libstemmer.h -> ../../snowball/snowball.git/include/libstemmer.h

    # https://github.com/OSGeo/proj.4.git
    # https://github.com/libspatialindex/libspatialindex.git

    camptocamp_login = ctx.source_path.joinpath('unit-tests', 'camptocamp', 'login.h')
    if not camptocamp_login.exists():
        raise NameError(f"{camptocamp_login} is missing")

####################################################################################################

@task()
def linguist(ctx):
    ts_path = ctx.source_path.joinpath('translations', 'alpine-toolkit.fr_FR.ts')
    ctx.run(f'linguist {ts_path}')

####################################################################################################

@task()
def qml(ctx, path):
    _set_qt(ctx)

    path = Path(path)
    if not (path.exists() and path.is_dir()):
        print(f"Directory {path} doesn't exist")
    qml_path = ctx.qt_path_bin.joinpath('qml')
    main_qml = 'main.qml'
    includes = ' '.join([f'-I {_}' for _ in ('qml',)])
    command = f'{qml_path} {includes} {main_qml}'
    env = {}
    with ctx.cd(path):
        ctx.run(command, env=env)

####################################################################################################

@task(
    pre=[init_source],
    optional=['qt', 'ndk', 'sdk'],
)
def build(
        ctx,

        qt=None,
        arch='gcc_64',
        ndk=None,
        sdk=None,

        cmake=True,
        clean=False,
        ninja=True,
        make=False,
):

    ARCH = (
        'gcc_64',
        'android_armv7',
    )
    if arch not in ARCH:
        raise NameError(f"arch must be {ARCH}")

    is_android = arch.startswith('android')

    _set_qt(ctx, qt, arch)

    # Fixme:_arch
    build_path = ctx.source_path.joinpath('build-cmake')

    cflags = '-g -O0'
    # https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
    # '-O3 -march=broadwell -mtune=broadwell -flto'
    build_type = 'DEBUG' # 'RELEASE'

    env = {
        'LC_ALL': 'C',
        'CFLAGS': cflags,
        'CXXFLAGS': cflags,
        # 'CMAKE_PREFIX_PATH': str(ctx.qt_path_lib.joinpath('cmake'))
    }

    print()
    print(f"Source path: {ctx.source_path}")
    print(f"Build path: {build_path}")
    print(f'Qt path: {ctx.qt_path}')
    print(f"Arch: {arch}")
    print(f"Build type: {build_type}")
    # print(f"Env: {env}")
    print(f"CXXFLAGS: {env['CXXFLAGS']}")
    if is_android:
        print(f"NDK path: {ndk}")
        print(f"SDK path: {sdk}")
    print()

    if not build_path.exists():
        build_path.mkdir()

    with ctx.cd(build_path):

        if clean:
            for _ in (
                    'CMakeCache.txt',
                    'compile_commands.json',
            ):
                os.unlink(_)
            if Path('Makefile').exists():
                ctx.run('make clean')

        if cmake:
            # /etc/security/limits.d/00-user.conf

            command = [
                'cmake',
                f'-S {ctx.source_path}',
                f'-B {build_path}',

                '-G Ninja' if ninja else '',
                # -D CMAKE_GENERATOR:STRING=Ninja

                f'-D CMAKE_BUILD_TYPE:STRING={build_type}',

                f'-D CMAKE_PREFIX_PATH:PATH={ctx.qt_arch_path}',
                f'-D CMAKE_FIND_ROOT_PATH:PATH={ctx.qt_arch_path}',
                f'-D QT_HOST_PATH:PATH={ctx.qt_host_path}',
            ]

            # -DCMAKE_PROJECT_INCLUDE_BEFORE:FILEPATH=/srv/qt/Qt/Tools/QtCreator/share/qtcreator/package-manager/auto-setup.cmake

            if is_android:
                ndk = Path(ndk)
                sdk = Path(sdk)
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
                    f'-D QT_QMAKE_EXECUTABLE:FILEPATH={ctx.qmake_path}',
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
            ctx.run(command, pty=True, echo=True, env=env)
            ctx.run(f'cmake --build {build_path} --target alpine-toolkit_lupdate', pty=True, echo=True)

        # cmake --build {build_path} --target all
        if ninja:
            # -C build-cmake
            # -j 4
            ctx.run('ninja', pty=True)
        elif make:
            # -k
            ctx.run('make -j4', pty=True)

        # /srv/qt/Qt/6.3.0/gcc_64/bin/androiddeployqt
        # --input {build_path}/android-touch-app-deployment-settings.json
        # --output {build_path}/android-build
        # --android-platform android-31
        # --jdk /usr/lib/jvm/java-openjdk
        # --gradle

####################################################################################################

@task()
def unit_test(ctx):
    _set_source_path(ctx)
    build_path = ctx.source_path.joinpath('build-cmake')
    unit_test_path = build_path.joinpath('unit-tests')

    print('Run unit tests...')
    tests = []
    failed = []
    for root, _, filenames in os.walk(unit_test_path):
        root = Path(root)
        for filename in filenames:
            filename = root.joinpath(filename)
            if os.access(filename, os.X_OK):   # Fixme: Unix
                filename_part = str(filename).replace(str(build_path.parent), '.')
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
#    pre=[call(build, qt=qt)],
)
def run(ctx,
        qt=None,
        ):
    _set_source_path(ctx)
    build_path = ctx.source_path.joinpath('build-cmake')

    env = {
        'QT_LOGGING_RULES': '*.debug=false;*.info=true;alpine-toolkit.qtcarto.debug=true',

        # QT_GEOCLUE_APP_DESKTOP_ID=alpine-toolkit

        # ALPINE_TOOLKIT_MOCKUP=TRUE
        # ALPINE_TOOLKIT_FAKE_ANDROID=TRUE
        # QML_IMPORT_TRACE=1
        # ASAN_OPTIONS=new_delete_type_mismatch=0
        # QT_QUICK_CONTROLS_STYLE=material
    }

    # clear ; ninja -j2 &&
    command = build_path.joinpath('src', 'alpine-toolkit')
    ctx.run(command, env=env)
