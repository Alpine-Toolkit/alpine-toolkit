// -*- mode: c++ -*-

/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire.
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine Toolkit software.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $ALPINE_TOOLKIT_END_LICENSE$
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
