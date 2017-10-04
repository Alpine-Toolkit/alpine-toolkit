#! /bin/bash

####################################################################################################

source_path=/home/fabrice/home/developpement/qtcarto-application/alpine-toolkit
build_path=${source_path}/build-cmake

# QT_VERSION=5.7
# QT_VERSION=5.8
# QT_VERSION=5.9
# QT_VERSION=5.9.1
QT_VERSION=5.10.0

export CFLAGS="-g -O0"
export CXXFLAGS="${CFLAGS}"
BUILD_TYPE=DEBUG

# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
# set_gcc_optimisation
# export CFLAGS="-O3 -march=broadwell -mtune=broadwell -flto"
# export CXXFLAGS="${CFLAGS}"
# BUILD_TYPE=RELEASE

####################################################################################################

source $HOME/.bashrc

append_to_path_if_not /opt/Qt/${QT_VERSION}/gcc_64/bin/
append_to_ld_library_path_if_not /opt/Qt/${QT_VERSION}/gcc_64/lib/

if ! [ -e ${build_path} ]; then
  mkdir ${build_path}
fi
pushd ${build_path}

rm CMakeCache.txt
rm compile_commands.json
make clean

cmake \
  -D CMAKE_BUILD_TYPE:STRING=={BUILD_TYPE} \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DSANITIZE=ON \
  -DINSTRUMENT_FUNTIONS=OFF \
  ${source_path}

make -j4
