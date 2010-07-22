#ifndef h_KTEXTPLUGIN_MANAGER
#define h_KTEXTPLUGIN_MANAGER

#include "KTextPluginInstance.h"
#include "KTextPluginNativeModuleBase.h"
#include "KTextPluginNativeBridge.h"

#include "KTextEdit2.h"
#include "ktextplugin_export.h"
#include <QScriptEngine>
#include <KDebug>

class LIBKTEXTPLUGIN_EXPORT KTextPluginManager : public QObject{
  Q_OBJECT
  
  public:
    KTextPluginManager(QObject *parent, KTextEdit2* _editor);
    ~KTextPluginManager();
    void addPlugin(QString path);
    
  private:
    void loadNativePlugin();
    
    QList<KTextPluginInstance*> m_instances;
    KTextEdit2* m_textArea;
    QScriptEngine* m_engine;
    
  public slots:
    void addNativePlugin(Plugin *plugin);
};

#endif