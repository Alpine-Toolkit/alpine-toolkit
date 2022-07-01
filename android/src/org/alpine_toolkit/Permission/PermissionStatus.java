/***************************************************************************************************
 **
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
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
    NeedExplain,
    NeedGrant,
    Denied,
  }

  private static AtomicInteger m_last_id = new AtomicInteger(0);

  private String m_permission;
  private int m_id;
  private PermissionState m_status;
  private boolean m_is_dangerous;
  private boolean m_is_explained;

  /**********************************************/

  public PermissionStatus(final String permission)
  {
    m_permission = permission;
    m_id = m_last_id.incrementAndGet();
    m_status = PermissionState.Unknown;
    m_is_dangerous = false;
    m_is_explained = false;
  }

  /**********************************************/

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

  public Boolean is_dangerous()
  {
    return m_is_dangerous;
  }

  public Boolean is_explained()
  {
    return m_is_explained;
  }

  /**********************************************/

  public void set_status(PermissionState status)
  {
    m_status = status;
  }

  public void set_granted()
  {
    set_status(PermissionState.Granted);
  }

  public void set_need_explain()
  {
    m_is_dangerous = true;
    m_is_explained = false;
    set_status(PermissionState.NeedExplain);
  }

  public void set_as_explained()
  {
    m_is_explained = true;
    set_need_grant();
  }

  public void set_need_grant()
  {
    set_status(PermissionState.NeedGrant);
  }

  public void set_denied()
  {
    set_status(PermissionState.Denied);
  }

  /**********************************************/

  public Boolean is_granted()
  {
    return m_status == PermissionState.Granted;
  }

  public Boolean is_need_explain()
  {
    return m_status == PermissionState.NeedExplain;
  }

  public Boolean is_need_grant()
  {
    return m_status == PermissionState.NeedGrant;
  }

  public Boolean is_denied()
  {
    return m_status == PermissionState.Denied;
  }
}
