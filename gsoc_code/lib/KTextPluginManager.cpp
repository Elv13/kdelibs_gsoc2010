#include "KTextPluginManager.h"

KTextPluginManager::KTextPluginManager(QObject *parent, KTextEdit2* _editor):QObject(parent),m_textArea(_editor)
{
  m_engine = new QScriptEngine(this);
  loadNativePlugin();
}

KTextPluginManager::~KTextPluginManager()
{
  delete m_engine;
}

void KTextPluginManager::addPlugin(QString path)
{
  //QScriptEngine *pEngine = new QScriptEngine(this);
  KTextPluginInstance* aScript = new KTextPluginInstance(m_engine, m_textArea, this);
  aScript->runScript(path);
  m_instances << aScript;
}

void KTextPluginManager::loadNativePlugin()
{
  qDebug() << "loadPlugin()";
  PluginLoader *loader = new PluginLoader(this);
    connect(loader, SIGNAL(pluginLoaded(Plugin*)), this, SLOT(addPlugin(Plugin*)));
    loader->loadAllPlugins();
}

void KTextPluginManager::addNativePlugin(Plugin *plugin)
{
    //editor = plugin->editorInterface();
    //guiFactory()->addClient(plugin);
    qDebug() << "Work!!!!! " << plugin->provide();
    QScriptValue objectValue = m_engine->newQObject(plugin);
    foreach (QString provide, plugin->provide()) {
      m_engine->globalObject().setProperty(provide, objectValue);
    }
}