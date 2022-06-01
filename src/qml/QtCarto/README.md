# QtCarto Module {#qtcarto-qml-module}

---
**Notes**

* How is found the module by the `alpine-tookit` application ?
  `QtCarto` module sources are includes in `qtcarto` library, cf. `src/qtcarto/CMakelists.txt`
  `QmlRegisterType(QcMapItem);`

---

# QML Module

* https://doc.qt.io/qt-6/qtqml-writing-a-module.html
* https://doc.qt.io/qt-6/qtqml-modules-qmldir.html
* https://doc.qt.io/qt-6/qt-add-qml-module.html
* https://doc.qt.io/qt-6/qtqml-syntax-imports.html

**Module Example**
```
.../Qt/6.3.0/gcc_64/qml/QtQuick/Controls/Material/
qmldir
libqtquickcontrols2materialstyleplugin.so
*.qml
```

**To debug import**
`QML_IMPORT_TRACE=1 app`
see https://doc.qt.io/qt-6/qtquick-debugging.html#debugging-module-imports

# Design

```
QtCartoDeclarativeModule > QQmlExtensionPlugin

QcMapItem > QQuickItem

QcGeoCoordinateAnimation > QQuickPropertyAnimation

QcMapGestureArea > QQuickItem
QcMapPinchEvent > QObject
```
