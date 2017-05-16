#! /usr/bin/bash

####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the QtCarto library.
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
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# $ALPINE_TOOLKIT_END_LICENSE$
#
####################################################################################################

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
