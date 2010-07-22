include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_SHARED)


Set (MakeCompleToolsPlugin_SRC TestNative.cpp)

kde4_add_plugin(ktextplugin_testnative ${MakeCompleToolsPlugin_SRC} )
target_link_libraries(ktextplugin_testnative 
                          ${KDE4_KDEUI_LIBS}
	  ktextplugin)

install(TARGETS ktextplugin_testnative  DESTINATION ${PLUGIN_INSTALL_DIR})

install( FILES ktextplugin_testnative.desktop  DESTINATION ${SERVICES_INSTALL_DIR})