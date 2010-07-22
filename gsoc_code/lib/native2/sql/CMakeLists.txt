CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(
        ${KDE4_DEFINITIONS}
        ${QT_DEFINITIONS}
        -fexceptions
)


ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_SHARED)

#PROJECT(ktextpluginNative_Sql)

#target_link_libraries(ktextpluginNative_File ${QT_QTCORE_LIBRARY} ${KDE4_KDEUI_LIBS})

SET(LOCAL_CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
SET(CMAKE_MODULE_PATH "${LOCAL_CMAKE_MODULE_PATH}")

FIND_PACKAGE ( KDE4 REQUIRED )
FIND_PACKAGE ( Qt4 REQUIRED )

INCLUDE ( KDE4Defaults )

set(GENERIC_LIB_VERSION "0.1")

INCLUDE_DIRECTORIES ( ${KDE4_INCLUDES} ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})



#File to compile
set( ktextpluginNative_Sql_LIB_SRCS
  sql.cpp
)

kde4_add_plugin(ktextpluginNative_Sql ${ktextpluginNative_Sql_LIB_SRCS} )
target_link_libraries(ktextpluginNative_Sql 
		      ${KDE4_KDEUI_LIBS}
		      ${QT_QTSQL_LIBRARY}
		      QtScript
		      ktextplugin)
  
install(TARGETS ktextpluginNative_Sql  DESTINATION ${PLUGIN_INSTALL_DIR})

install( FILES ktextpluginNative_Sql.desktop  DESTINATION ${SERVICES_INSTALL_DIR})


# kde4_add_library( ktextpluginNative_File  SHARED ${ktextpluginNative_Sql_LIB_SRCS} )
# 
# target_link_libraries( ktextpluginNative_File
#   ${KDE4_KDECORE_LIBS}
#   ${QT_QTCORE_LIBRARY}
#   ${KDE4_KDEUI_LIBS} 
#   ${QT_QTSQL_LIBRARY}
#   QtScript
# )
# 
# set_target_properties( ktextpluginNative_File
#   PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION}
# )
# 
# 
# install( FILES ${ktextpluginNative_File_LIB_HDRS}
#   DESTINATION ${INCLUDE_INSTALL_DIR}/ktextpluginNative_File
#   COMPONENT Devel
# )
# 
# install( TARGETS ktextpluginNative_File  ${INSTALL_TARGETS_DEFAULT_ARGS} )
