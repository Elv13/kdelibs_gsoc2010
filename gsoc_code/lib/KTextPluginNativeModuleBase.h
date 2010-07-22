#ifndef h_KTEXTPLUGIN_NATIVE_MODULE_BASE
#define h_KTEXTPLUGIN_NATIVE_MODULE_BASE

#include <QObject>
 
#include "KTextPluginMacro.h"
 
class Plugin;
 
class PluginLoader : public QObject
{
    Q_OBJECT
    public:
        PluginLoader(QObject * parent);
        virtual ~PluginLoader();
 
        void loadAllPlugins();
 
    signals:
        void pluginLoaded(Plugin * plugin);
};
#endif