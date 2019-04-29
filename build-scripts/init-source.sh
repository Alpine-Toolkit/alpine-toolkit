third_parties=$HOME/home/developpement/qtcarto-application/alpine-toolkit/third-parties

pushd third-parties/
if [ ! -e include ]; then
  cp -r ${third_parties}/include/ .
fi
pushd cmark/
if [ ! -e cmark.git ]; then
  ln -sf ${third_parties}/cmark/cmark.git/ .
fi
popd
popd

# QT_VERSION=5.7
# QT_VERSION=5.8
QT_VERSION=5.9
append_to_path_if_not /opt/Qt/${QT_VERSION}/gcc_64/bin/

lupdate alpine-toolkit.pro
lrelease alpine-toolkit.pro

mkdir -p build-cmake
