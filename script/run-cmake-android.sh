####################################################################################################

# QT_VERSION=5.7
# QT_VERSION=5.8
QT_VERSION=5.9
append_to_path_if_not /opt/Qt/${QT_VERSION}/gcc_64/bin/

# -DANDROID_ABI="armeabi-v7a with NEON"

#BUILD_TYPE=Release
BUILD_TYPE=Debug

# arm64-v8a

cmake \
  -DCMAKE_SYSTEM_NAME=Android \
  -DCMAKE_SYSTEM_VERSION=21 \
  -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a \
  -DCMAKE_ANDROID_NDK=/opt/android-ndk-r10e \
  -DCMAKE_ANDROID_STL_TYPE=gnustl_static \
  -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
  -DCMAKE_C_FLAGS="-o3" \
  -DCMAKE_CXX_FLAGS="-o3" \
  $HOME/home/developpement/qtcarto-application/alpine-toolkit

# cmake --build .

####################################################################################################
#
# End
#
####################################################################################################
