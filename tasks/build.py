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

from invoke import task

####################################################################################################

@task
def set_source_path(ctx):
    ctx.source_path = Path(__file__).parents[1]

####################################################################################################

@task
def set_qt(ctx):
    ctx.qt_path = Path(os.getenv('QT_PATH'))
    match sys.platform:
        case 'linux':
            arch = 'gcc_64'
            ctx.qt_path_bin = ctx.qt_path.joinpath(arch, 'bin')
            ctx.qt_path_lib = ctx.qt_path.joinpath(arch, 'lib')
        case 'darwin':
            raise NotImplementedError
        case 'win32':
            raise NotImplementedError

####################################################################################################

@task(set_qt)
def qml(ctx, path):
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

@task(set_qt, set_source_path)
def build_x86(ctx, cmake=True, clean=False, ninja=True, make=False):

    build_path = ctx.source_path.joinpath('build-cmake')

    cflags = '-g -O0'
    # https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
    # '-O3 -march=broadwell -mtune=broadwell -flto'
    build_type = 'DEBUG' # 'RELEASE'

    env = {
        'LC_ALL': 'C',
        'CFLAGS': cflags,
        'CXXFLAGS': cflags,
        'CMAKE_PREFIX_PATH': str(ctx.qt_path_lib.joinpath('cmake'))
    }

    print(f"Source path: {ctx.source_path}")
    print(f"Build path: {build_path}")
    print(f"Env: {env}")
    print(f"Build type: {build_type}")

    if not build_path.exists():
        os.mkdir(build_path)

    with ctx.cd(build_path):

        if clean:
            for _ in (
                    'CMakeCache.txt',
                    'compile_commands.json',
            ):
                ctx.run('rm -f {_}')
            if Path('Makefile').exists():
                ctx.run('make clean')

        if cmake:
            # /etc/security/limits.d/00-user.conf
            # -DSANITIZE=ON

            # https://sarcasm.github.io/notes/dev/compilation-database.html#cmake
            #   -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
            #     This will create a file name compile_commands.json in the build directory.

            command = ' '.join((
                'cmake',
                '-GNinja' if ninja else '',
                f'-D CMAKE_BUILD_TYPE:STRING=={build_type}',
                '-DCMAKE_EXPORT_COMPILE_COMMANDS=ON',
                '-DSANITIZE=OFF',
                '-DINSTRUMENT_FUNTIONS=OFF',
                str(ctx.source_path),
            ))
            ctx.run(command, pty=True, echo=True)

        if ninja:
            # -C build-cmake
            # -j 4
            ctx.run('ninja', pty=True)
        elif make:
            # -k
            ctx.run('make -j4', pty=True)

        # run-asan.sh
        # clear ; ninja -j2 && QT_LOGGING_RULES="*.debug=false;*.info=true;alpine-toolkit.qtcarto.debug=true" ./src/alpine-toolkit
