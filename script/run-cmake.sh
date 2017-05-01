# QT_VERSION=5.7
# QT_VERSION=5.8
QT_VERSION=5.9
append_to_path_if_not /opt/Qt/${QT_VERSION}/gcc_64/bin/
append_to_ld_library_path_if_not /opt/Qt/${QT_VERSION}/gcc_64/lib/

export CFLAGS="-g -O0"
export CXXFLAGS="${CFLAGS}"
BUILD_TYPE=DEBUG

# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
# set_gcc_optimisation
# export CFLAGS="-O3 -march=broadwell -mtune=broadwell -flto"
# export CXXFLAGS="${CFLAGS}"
# BUILD_TYPE=RELEASE

cmake \
  -D CMAKE_BUILD_TYPE:STRING=={BUILD_TYPE} \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DSANITIZE=OFF \
  -DINSTRUMENT_FUNTIONS=OFF \
  /home/fabrice/home/developpement/qtcarto-application/alpine-toolkit
