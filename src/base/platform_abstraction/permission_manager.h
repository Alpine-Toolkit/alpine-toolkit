// -*- mode: c++ -*-

/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef PERMISSION_MANAGER_H
#define PERMISSION_MANAGER_H

#include <functional>

#include <QHash>
#include <QList>
#include <QObject>

/**************************************************************************************************/

class PermissionManager : public QObject
{
  Q_OBJECT

public:
  typedef std::function<void(const QString & permission, bool granted)> PermissionCallback;
  typedef QList<PermissionCallback> PermissionCallbackList;

public:
  PermissionManager();
  ~PermissionManager();

  virtual Q_INVOKABLE bool require_write_permission(const QString & path) const; // Fixme: Q_INVOKABLE ???

   // async
  void check_permission(const QString & permission, const PermissionCallback & callback);

signals:
  void open_explain_permission(const QString & permission, const QString & explanation);

public slots:
  void on_accepted_explain_permission(const QString & permission);
  void on_rejected_explain_permission(const QString & permission);

protected:
  virtual bool need_explain(const QString & permission) = 0;
  QString permission_explanation(const QString & permission) const;

  virtual bool is_permission_granted(const QString & permission) const = 0;

  virtual void request_permission(const QString & permission) = 0;

  void register_callback(const QString & permission, const PermissionCallback & callback);
  void call_callback(const QString & permission, bool granted);

private:
  QHash<QString, PermissionCallbackList> m_callbacks;
};

/**************************************************************************************************/

#endif // PERMISSION_MANAGER_H
