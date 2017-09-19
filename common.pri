# -*- mode:qmake -*-

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

####################################################################################################

CONFIG += debug
# CONFIG += release
# CONFIG += debug_and_release

BUILD_AS_SHARED = 1
# BUILD_AS_STATIC = 1

defined(BUILD_AS_SHARED, var) {
    message("Build $$TARGET as shared")
}
defined(BUILD_AS_STATIC, var) {
    message("Build $$TARGET as static")
}

####################################################################################################

CONFIG += ordered # process directories in order

# CONFIG += precompile_header

CONFIG += qt

CONFIG += c++11
CONFIG += c++14

# For statical linking
CONFIG += create_prl
CONFIG += link_prl

debug {
 CONFIG += console
}

####################################################################################################

linux:!android {
DEFINES += ON_LINUX
}

android {
message("Android arch is $$ANDROID_TARGET_ARCH") # x86 armeabi-v7a

DEFINES += ANDROID
DEFINES += ON_ANDROID
}

####################################################################################################