if [ -e android/src/org/qtproject ]; then
  rm android/src/org/qtproject
else
  pushd android/src/org/
  ln -sf /home/opt/Qt/5.10.0/android_armv7/src/android/java/src/org/qtproject
  popd
fi
ll android/src/org/qtproject
