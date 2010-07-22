#include "KTextPluginNativeModuleBase.h"
#include "KTextPluginNativeBridge.h"
#include <KServiceTypeTrader>
#include <KDebug>
 
PluginLoader::PluginLoader(QObject * parent)
  : QObject(parent)
{
  loadAllPlugins();
}
 
PluginLoader::~PluginLoader()
{
}
 
void PluginLoader::loadAllPlugins()
{
    kDebug() << "Load all plugins";
    KService::List offers = KServiceTypeTrader::self()->query("KTextPlugin/Native");
 
    KService::List::const_iterator iter;
    for(iter = offers.begin(); iter < offers.end(); ++iter)
    {
       QString error;
       KService::Ptr service = *iter;
 
        KPluginFactory *factory = KPluginLoader(service->library()).factory();
 
        if (!factory)
        {
            //KMessageBox::error(0, i18n("<html><p>KPluginFactory could not load the plugin:<br/><i>%1</i></p></html>",
              //                         service->library()));
            kError(5001) << "KPluginFactory could not load the plugin:" << service->library();
            continue;
        }
 
       Plugin *plugin = factory->create<Plugin>(this);
 
       if (plugin) {
           kDebug() << "Load plugin:" << service->name();
           emit pluginLoaded(plugin);
       } else {
           kDebug() << error;
       }
    }
}