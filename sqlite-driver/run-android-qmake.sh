export ANDROID_NDK_ROOT=/opt/android-ndk-r10e
/opt/Qt/5.9/android_armv7/bin/qmake -o Makefile ../sqlite.pro -spec android-g++ CONFIG+=debug CONFIG+=qml_debug
