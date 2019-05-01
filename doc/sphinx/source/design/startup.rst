Application Startup
===================

1. Start Activity implemented in :file:`android/src/org/alpine_toolkit/AlpineToolkitActivity.java`

   * copy assets to :file:`/data/user/0/org.alpine_toolkit/files/assets/`

1. Load :file:`.so` libraries

1. :file:`src/main.cpp`

  * :code:`qInstallMessageHandler()`
  * :code:`Application::create()`
  * :code:`application.exec()`
