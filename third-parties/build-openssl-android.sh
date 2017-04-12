#! /usr/bin/bash

# http://doc.qt.io/qt-5/opensslsupport.html

####################################################################################################

# tar xzf openssl-1.0.2h.tar.gz
# pushd openssl-1.0.2h

####################################################################################################

ANDROID_NDK_PATH=/home/opt/android-ndk-r10e
VERSION=4.9
NDK_HOST=linux-x86_64
ANDROID_PLATFORM=android-21

####################################################################################################

export CC=${ANDROID_NDK_PATH}/toolchains/arm-linux-androideabi-${VERSION}/prebuilt/${NDK_HOST}/bin/arm-linux-androideabi-gcc
export AR=${ANDROID_NDK_PATH}/toolchains/arm-linux-androideabi-${VERSION}/prebuilt/${NDK_HOST}/bin/arm-linux-androideabi-ar

export ANDROID_DEV=${ANDROID_NDK_PATH}/platforms/${ANDROID_PLATFORM}/arch-arm/usr

echo $CC
echo $AR
echo ${ANDROID_DEV}

if [ ! -e $CC ]; then
  echo Cannot found CC
  exit 1
fi
if [ ! -e $AR ]; then
  echo Cannot found AR
  exit 1
fi
if [ ! -e $AR ]; then
  echo "ANDROID_DEV don't exist"
  exit 1
fi

####################################################################################################

# compile with -march=armv7-a -O3

make clean

./Configure shared android-armv7

sed -e 's/LIBNAME=$$i LIBVERSION=$(SHLIB_MAJOR).$(SHLIB_MINOR)/LIBNAME=$$i/' -i Makefile
sed -e '/LIBCOMPATVERSIONS=";$(SHLIB_VERSION_HISTORY)"/d' -i Makefile

make depend
make -j4
