####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

set(alpine_toolkit_qml_files
  qml/main.qml

  qml/Constants/Style.qml

  qml/Widgets/About.qml
  qml/Widgets/CompassRose.qml
  qml/Widgets/Dialog.qml
  qml/Widgets/ExplainPermission.qml
  qml/Widgets/Layers.qml
  qml/Widgets/MapComponent.qml
  qml/Widgets/MenuItemIcon.qml
  qml/Widgets/OptionsMenu.qml
  qml/Widgets/Page.qml
  qml/Widgets/Popup.qml
  qml/Widgets/Projections.qml
  qml/Widgets/SplashScreen.qml

  qml/C2cFilter/ActivityFilter.qml
  qml/C2cFilter/CheckBoxFilter.qml
  qml/C2cFilter/CompassRoseFilter.qml
  qml/C2cFilter/Filter.qml
  qml/C2cFilter/GradeRangeSliderFilter.qml
  qml/C2cFilter/RangeSliderFilter.qml

  qml/Settings/SettingsPageModel.qml
  qml/Settings/ApplicationDirectory.qml

  qml/PageModel.qml
  qml/Pages/Altimeter.qml
  qml/Pages/Bleau.qml
  qml/Pages/Camera.qml
  qml/Pages/Camptocamp.qml
  qml/Pages/CamptocampCache.qml
  qml/Pages/CamptocampLogin.qml
  qml/Pages/CamptocampMedia.qml
  qml/Pages/CamptocampRoute.qml
  qml/Pages/CamptocampSearchFilter.qml
  qml/Pages/Chart.qml
  qml/Pages/Checklist.qml
  qml/Pages/DataLogger.qml
  qml/Pages/Emergency.qml
  qml/Pages/Ephemeride.qml
  qml/Pages/FuelGauge.qml
  qml/Pages/Gps.qml
  qml/Pages/HeartRate.qml
  qml/Pages/Illuminance.qml
  qml/Pages/Inclination.qml
  qml/Pages/LampSignal.qml
  qml/Pages/Map.qml
  qml/Pages/PersonCounter.qml
  qml/Pages/Refuge.qml
  qml/Pages/RefugeDirectory.qml
  qml/Pages/Settings.qml
  qml/Pages/Torch.qml
  qml/Pages/UiTest.qml
)

####################################################################################################

# https://doc.qt.io/qt-6/qtlinguist-cmake-qt-add-translations.html
qt6_add_translations(alpine-toolkit
  TS_FILES translations/alpine-toolkit.fr_FR.ts
  RESOURCE_PREFIX "/translations"
  SOURCES ${alpine_toolkit_qml_files}
)

####################################################################################################

# https://doc.qt.io/qt-6/qt-add-resources.html

qt6_add_resources(alpine-toolkit "qml_files"
  PREFIX "/"
  FILES
  qml/qmldir
  qml/Constants/qmldir
  qml/Widgets/qmldir
  qml/C2cFilter/qmldir
  qml/Settings/qmldir
  qml/Pages/qmldir
  ${alpine_toolkit_qml_files}
)

qt6_add_resources(alpine-toolkit "js_files"
  PREFIX "/"
  FILES
  js/android_permission.js
  js/camptocamp_definitions.js
  js/camptocamp_search_filter.js
  js/camptocamp_search_filter_definitions.js
  js/compass_rose.js
  js/gps.js
  js/math.js
  js/set.js
)

qt6_add_resources(alpine-toolkit "conf_files"
  PREFIX "/"
  FILES
  qtquickcontrols2.conf
)

qt6_add_resources(alpine-toolkit "fonts"
  PREFIX "/"
  FILES
  fonts/c2c-activities.ttf
)

qt6_add_resources(alpine-toolkit "icons"
  PREFIX "/"
  FILES
  application-icons/icon-512.png
  application-icons/icon.svg
  application-icons/icon-transparent-512.png
  application-icons/icon-transparent.svg

  # icons/close-black.png
  # icons/close-black@3x.png
  icons/add-black.png
  icons/add-black@3x.png
  icons/arrow-back-white.png
  icons/arrow-back-white@3x.png
  icons/build-black.png
  icons/build-black@3x.png
  icons/call-black.png
  icons/call-black@3x.png
  icons/clear-black.png
  icons/clear-black@3x.png
  icons/cloud-done-black.png
  icons/cloud-done-black@3x.png
  icons/cloud-download-black.png
  icons/cloud-download-black@3x.png
  icons/data-logger-black.png
  icons/data-logger-black@3x.png
  icons/delete-black.png
  icons/delete-black@3x.png
  icons/explore-black.png
  icons/explore-black@3x.png
  icons/filter-black.png
  icons/filter-black@3x.png
  icons/folder-black.png
  icons/folder-black@3x.png
  icons/gps-fixed-black.png
  icons/gps-fixed-black@3x.png
  icons/gps-not-fixed-black.png
  icons/gps-not-fixed-black@3x.png
  icons/gps-off-black.png
  icons/gps-off-black@3x.png
  icons/help-black.png
  icons/help-black@3x.png
  icons/menu-white.png
  icons/menu-white@3x.png
  icons/more-vert-white.png
  icons/more-vert-white@3x.png
  icons/navigation-black.png
  icons/navigation-black@3x.png
  icons/people-black.png
  icons/people-black@3x.png
  icons/person-black.png
  icons/person-black@3x.png
  icons/person-outline-black.png
  icons/person-outline-black@3x.png
  icons/remove-black.png
  icons/remove-black@3x.png
  icons/sd-card-black.png
  icons/sd-card-black@3x.png
  icons/search-black.png
  icons/search-black@3x.png
  icons/security-black.png
  icons/security-black@3x.png
  icons/settings-black.png
  icons/settings-black@3x.png
  icons/undo-black.png
  icons/undo-black@3x.png
  icons/volume-mute-black.png
  icons/volume-mute-black@3x.png
  icons/warning-black.png
  icons/warning-black@3x.png
  icons/wb-incandescent-black.png
  icons/wb-incandescent-black@3x.png
  icons/wb-sunny-black.png
  icons/wb-sunny-black@3x.png

  icons/altimeter-black.png
  icons/altimeter-black@3x.png
  icons/ambulance-black.png
  icons/ambulance-black@3x.png
  icons/area-black.png
  icons/area-black@3x.png
  icons/camptocamp-black.png
  icons/camptocamp-black@3x.png
  icons/clignometre-black.png
  icons/clignometre-black@3x.png
  icons/ephemeride-black.png
  icons/ephemeride-black@3x.png
  icons/fuel-black.png
  icons/fuel-black@3x.png
  icons/helicopter-black.png
  icons/helicopter-black@3x.png
  icons/hut-black.png
  icons/hut-black@3x.png
  icons/lamp-signal-black.png
  icons/lamp-signal-black@3x.png
  icons/light-bulb-black.png
  icons/light-bulb-black@3x.png
  # icons/light-bulb.svg
  icons/light-bulb-white.svg
  icons/map-black.png
  icons/map-black@3x.png
  icons/polyline-black.png
  icons/polyline-black@3x.png
  icons/polyline-dot-black.png
  icons/polyline-dot-black@3x.png
  icons/ruler-black.png
  icons/ruler-black@3x.png
  icons/settings-sliders-black.png
  icons/settings-sliders-black@3x.png
  icons/sun-black.png
  icons/sun-black@3x.png
  icons/torch-black.png
  icons/torch-black@3x.png
  icons/volume-white.svg
)

qt6_add_resources(alpine-toolkit "tone"
  PREFIX "/"
  FILES
  tones/long-pause.ogg
  tones/long-pulse.ogg
  tones/short-pause.ogg
  tones/short-pulse.ogg
)

qt6_add_resources(alpine-toolkit "data"
  PREFIX "/"
  FILES
  data/bleau.json
  data/refuges.json
  data/stop-words.json
  data/third_party_licenses.json
  # data/ffcam-refuges.sqlite
)
