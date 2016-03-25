// -*- mode: c++ -*-

#ifndef ANDROID_ACTIVITY_H
#define ANDROID_ACTIVITY_H

#include <QObject>

class AndroidActivity : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool orientation_lock READ orientation_lock WRITE set_orientation_lock NOTIFY orientation_lockChanged)
  Q_PROPERTY(ScreenOrientation orientation READ orientation WRITE set_orientation NOTIFY orientationChanged)
  Q_PROPERTY(bool full_wave_lock READ full_wave_lock WRITE set_full_wave_lock NOTIFY full_wave_lockChanged)

public:
  explicit AndroidActivity(QObject *parent = 0);

  enum ScreenOrientation {
    Unspecified = Qt::UserRole + 1,
    Sensor,
    Portrait,
    Landscape,
  };
  typedef ScreenOrientation ScreenOrientation;
  Q_ENUMS(ScreenOrientation)

  void set_orientation_lock(bool orientation_lock);
  bool orientation_lock() const;

  void set_orientation(ScreenOrientation orientation);
  ScreenOrientation orientation() const;

  void set_full_wave_lock(bool full_wave_lock);
  bool full_wave_lock() const;

  Q_INVOKABLE void issue_call(const QString & phone_number);
  Q_INVOKABLE void issue_dial(const QString & phone_number);

signals:
  void orientation_lockChanged();
  void orientationChanged();
  void full_wave_lockChanged();

private slots:
  void update_orientation_lock();
  void update_orientation();
  void update_full_wave_lock();

private:
  bool m_orientation_lock;
  ScreenOrientation m_orientation;
  bool m_full_wave_lock;
};

#endif // ANDROID_ACTIVITY_H
