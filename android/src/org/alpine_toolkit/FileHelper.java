/***************************************************************************************************
**
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

package org.alpine_toolkit;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**************************************************************************************************/

public class FileHelper
{
  static public void delete_directory(File path)
  {
    if (path.isDirectory())
      for (File file : path.listFiles())
        delete_directory(file);

    path.delete();
  }

  static public void copy_file(InputStream input, OutputStream output) throws IOException
  {
    byte[] buffer = new byte[1024];
    while (input.read(buffer) != -1)
      output.write(buffer);
  }
}
