CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(
        ${KDE4_DEFINITIONS}
        ${QT_DEFINITIONS}
        -fexceptions
)

PROJECT(ktextplugin)

#target_link_libraries(ktextplugin ${QT_QTCORE_LIBRARY} ${KDE4_KDEUI_LIBS})

SET(LOCAL_CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
SET(CMAKE_MODULE_PATH "${LOCAL_CMAKE_MODULE_PATH}")

FIND_PACKAGE ( KDE4 REQUIRED )
FIND_PACKAGE ( Qt4 REQUIRED )

INCLUDE ( KDE4Defaults )

set(GENERIC_LIB_VERSION "0.1")

INCLUDE_DIRECTORIES ( ${KDE4_INCLUDES} ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})



#File to compile
set( ktextplugin_LIB_SRCS
  KTextPluginInstance.cpp  
  KTextPluginManager.cpp  
  KTextPluginNativeBridge.cpp  
  KTextPluginNativeModuleBase.cpp
  KTextEdit2.cpp
)

kde4_add_library( ktextplugin  SHARED ${ktextplugin_LIB_SRCS} )

target_link_libraries( ktextplugin
  ${KDE4_KDECORE_LIBS}
  ${QT_QTCORE_LIBRARY}
  ${KDE4_KDEUI_LIBS}
  QtScript
)

set_target_properties( ktextplugin
  PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION}
)

# set( ktextplugin_LIB_HDRS
#   Account.h
#   AccountList.h
#   Call.h
#   CallModel.h
#   CallTreeItem.h
#   Contact.h
#   ContactItemWidget.h
#   Item.h
#   libktextplugin_export.h
#   configurationmanager_interface_singleton.h
#   callmanager_interface_singleton.h
#   instance_interface_singleton.h
#   sflphone_const.h
# )

add_subdirectory(native)

install( FILES ${ktextplugin_LIB_HDRS}
  DESTINATION ${INCLUDE_INSTALL_DIR}/ktextplugin
  COMPONENT Devel
)

install( TARGETS ktextplugin  ${INSTALL_TARGETS_DEFAULT_ARGS} )
