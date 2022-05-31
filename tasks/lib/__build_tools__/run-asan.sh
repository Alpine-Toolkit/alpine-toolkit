############################################################
#
# Run Alpin Toolkit
#
############################################################

# QT_GEOCLUE_APP_DESKTOP_ID=alpine-toolkit \

make -j4 && \
ALPINE_TOOLKIT_MOCKUP=TRUE \
ALPINE_TOOLKIT_FAKE_ANDROID=TRUE \
QML_IMPORT_TRACE=1 \
ASAN_OPTIONS=new_delete_type_mismatch=0 \
QT_QUICK_CONTROLS_STYLE=material \
src/alpine-toolkit
