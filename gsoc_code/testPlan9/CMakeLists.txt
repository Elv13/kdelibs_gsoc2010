project(testplan9)
 
find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES})

add_subdirectory(lib)

set(testplan9_SRCS 
  main.cpp
  mainwindow.cpp
  KPushButton2.cpp
  KActionArg.cpp
  KToolBar2.cpp
  #KtextEdit2.cpp
  #KTextPluginInstance.cpp
  #KTextPluginManager.cpp
  #KTextPluginNativeBridge.cpp
  #KTextPluginNativeModuleBase.cpp
  #native/TestNative.cpp
)
 
kde4_add_executable(testplan9 ${testplan9_SRCS})
 
target_link_libraries(testplan9 ktextplugin ${KDE4_KDEUI_LIBS} QtScript)
 
install(TARGETS testplan9 DESTINATION ${BIN_INSTALL_DIR})
install(FILES testplan9ui.rc DESTINATION  ${DATA_INSTALL_DIR}/testplan9)
#install( FILES native/ktextplugin_testnative.desktop  DESTINATION ${SERVICES_INSTALL_DIR})

#kde4_add_plugin(ktextnative_testnative ${testplan9_SRCS} )