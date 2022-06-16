#! /usr/bin/bash

rm -f patch.diff

FILENAME=log
EXT=cpp
FILE_PATH=proj.git/src/${FILENAME}
diff -Naur ${FILE_PATH}.orig.${EXT} ${FILE_PATH}.new.${EXT} \
  | sed -e "s/${FILENAME}.orig.${EXT}/${FILENAME}.${EXT}/;s/${FILENAME}.new.${EXT}/${FILENAME}.${EXT}/" >> patch.diff

FILENAME=lib_proj
EXT=cmake
FILE_PATH=proj.git/src/${FILENAME}
diff -Naur ${FILE_PATH}.orig.${EXT} ${FILE_PATH}.new.${EXT} \
  | sed -e "s/${FILENAME}.orig.${EXT}/${FILENAME}.${EXT}/;s/${FILENAME}.new.${EXT}/${FILENAME}.${EXT}/" >> patch.diff

less patch.diff
