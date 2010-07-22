#include <QStringList>
#include <QScriptValue>
#include <QScriptEngine>
#include "../../KTextPluginNativeBridge.h"

class KatePlugin : public Plugin {
  public:
    KatePlugin(QObject* parent = 0) : Plugin(parent) {}
  public slots:
    QString documentPath();
    QString documentName();
    QString fileType();
    QString sessionName();
    virtual QStringList provide() {return QStringList("kate");}
  private:
    QScriptEngine* m_pEngine;
};