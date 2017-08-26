/***************************************************************************************************
 **
 ** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 **
 ** Copyright (C) 2017 Fabrice Salvaire
 ** Contact: http://www.fabrice-salvaire.fr
 **
 ** This file is part of the QtCarto library.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 ** $ALPINE_TOOLKIT_END_LICENSE$
 **
 ***************************************************************************************************/

/**************************************************************************************************/

package org.alpine_toolkit.Permission;

import java.util.concurrent.atomic.AtomicInteger;

/**************************************************************************************************/

public class PermissionStatus
{
  public enum PermissionState
  {
    Unknown,
    Granted,
    Denied,
    NeedExplain,
    NeedGrant,
  }

  private static AtomicInteger m_last_id = new AtomicInteger(0);

  private String m_permission;
  private int m_id;
  private PermissionState m_status;

  /**********************************************/

  public PermissionStatus(final String permission)
  {
    m_permission = permission;
    m_status = PermissionState.Unknown;

    m_id = m_last_id.incrementAndGet();
  }

  public String permission()
  {
    return m_permission;
  }

  public int id()
  {
    return m_id;
  }

  public PermissionState status()
  {
    return m_status;
  }

  public void set_status(PermissionState status)
  {
    m_status = status;
  }

  public void set_granted()
  {
    set_status(PermissionState.Granted);
  }

  public void set_denied()
  {
    set_status(PermissionState.Denied);
  }

  public void set_need_explain()
  {
    set_status(PermissionState.NeedExplain);
  }

  public void set_need_grant()
  {
    set_status(PermissionState.NeedGrant);
  }

  public Boolean is_granted()
  {
    return m_status == PermissionState.Granted;
  }

  public Boolean is_denied()
  {
    return m_status == PermissionState.Denied;
  }

  public Boolean is_need_explain()
  {
    return m_status == PermissionState.NeedExplain;
  }

  public Boolean is_need_grant()
  {
    return m_status == PermissionState.NeedGrant;
  }
}
