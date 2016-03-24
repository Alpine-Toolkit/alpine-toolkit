// -*- mode: c++ -*-

#ifndef ANDROID_ACTIVITY_H
#define ANDROID_ACTIVITY_H

#include <QObject>

class AndroidActivity : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool orientation_lock READ orientation_lock WRITE set_orientation_lock NOTIFY orientationLockChanged)

public:
  explicit AndroidActivity(QObject *parent = 0);

  void set_orientation_lock(bool orientation_lock);
  bool orientation_lock() const;

  Q_INVOKABLE void issue_call(const QString & phone_number);

signals:
  void orientationLockChanged();

private slots:
  void updateOrientationLock();

private:
  bool m_orientation_lock;
};

#endif // ANDROID_ACTIVITY_H
