# QT_VERSION=5.7
# QT_VERSION=5.8
QT_VERSION=5.9
append_to_path_if_not /opt/Qt/${QT_VERSION}/gcc_64/bin/
append_to_ld_library_path_if_not /opt/Qt/${QT_VERSION}/gcc_64/lib/

export CFLAGS="-g -O0"
export CXXFLAGS="${CFLAGS}"
BUILD_TYPE=Debug

# set_gcc_optimisation
# BUILD_TYPE=Version

cmake \
  -D CMAKE_BUILD_TYPE:STRING=={BUILD_TYPE} \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  /home/fabrice/home/developpement/qtcarto-application/alpine-toolkit
