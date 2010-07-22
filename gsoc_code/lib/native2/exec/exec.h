#include <QStringList>
#include <QScriptValue>
#include <QScriptEngine>
#include <kdemacros.h>
#include "../../KTextPluginNativeBridge.h"

class KDE_EXPORT ExecPlugin : public Plugin {
  public:
    ExecPlugin(QObject* parent = 0) : Plugin(parent) {}
    bool exec(QString command, QStringList argv);
    QString findExecByName(QString command);
    QString findExecByMime(QString mime);
    QScriptValue listExecByMime(QString mime);
    bool setMime(QString mime, QString application);
    QString getIcon(QString application);
    int getPid(QString application);
  private:
    QScriptEngine* m_pEngine;
};