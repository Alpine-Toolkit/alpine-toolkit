####################################################################################################

# QT_VERSION=5.7
# QT_VERSION=5.8
QT_VERSION=5.9
append_to_path_if_not /opt/Qt/${QT_VERSION}/gcc_64/bin/

#BUILD_TYPE=Release
BUILD_TYPE=Debug

C_FLAGS="-o3 -m32" # To force 32-bit arch

cmake \
  -DCMAKE_SYSTEM_NAME=Android \
  -DCMAKE_SYSTEM_VERSION=21 \
  -DCMAKE_ANDROID_ARCH_ABI=x86 \
  -DCMAKE_ANDROID_NDK=/opt/android-ndk-r10e \
  -DCMAKE_ANDROID_STL_TYPE=gnustl_static \
  -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
  -DCMAKE_C_FLAGS="$C_FLAGS" \
  -DCMAKE_CXX_FLAGS="$C_FLAGS" \
  $HOME/home/developpement/qtcarto-application/alpine-toolkit

# cmake --build .

# Geos error
# error: expected unqualified-id before '__int128'
#        { typedef unsigned __int128 type; };

####################################################################################################
#
# End
#
####################################################################################################
