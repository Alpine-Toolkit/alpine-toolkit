# QtCarto Module {#qtcarto-qml-module}

---
**Notes**

* How is found the module by the `alpine-tookit` application ?
  `QtCarto` module sources are includes in `qtcarto` library, cf. `src/qtcarto/CMakelists.txt`
  `QmlRegisterType(QcMapItem);`
---

## Design

```
QtCartoDeclarativeModule > QQmlExtensionPlugin

QcMapItem > QQuickItem

QcGeoCoordinateAnimation > QQuickPropertyAnimation

QcMapGestureArea > QQuickItem
QcMapPinchEvent > QObject
```

## Gesture

```
class QcMapItem : public QQuickItem
{
  Q_PROPERTY(QcMapGestureArea * gesture READ gesture CONSTANT)

public:
  QcMapItem::QcMapItem(QQuickItem * parent)
  : m_gesture_area(new QcMapGestureArea(this))
  {}

  QcMapGestureArea * gesture() { return m_gesture_area; }

  void
  QcMapItem::mousePressEvent(QMouseEvent * event)
  {
     m_gesture_area->handle_mouse_press_event(event);
  }

  // called from map gesture area
  void on_wheel_event(const QWheelEvent * event);
  void on_press_and_hold(const QMouseEvent * event);
  void on_press_and_hold_released(const QMouseEvent * event);
  void on_double_clicked(const QMouseEvent * event);

protected:
  void mouseMoveEvent(QMouseEvent * event) Q_DECL_OVERRIDE ;
  void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE ;
  void mouseReleaseEvent(QMouseEvent * event) Q_DECL_OVERRIDE ;
  void mouseUngrabEvent() Q_DECL_OVERRIDE ;
  void touchEvent(QTouchEvent * event) Q_DECL_OVERRIDE ;
  void touchUngrabEvent() Q_DECL_OVERRIDE;
  void wheelEvent(QWheelEvent * event) Q_DECL_OVERRIDE ;

  // bool sendMouseEvent(QMouseEvent *event);
  // bool sendTouchEvent(QTouchEvent *event);

private:
  QcMapGestureArea * m_gesture_area;
}
```
