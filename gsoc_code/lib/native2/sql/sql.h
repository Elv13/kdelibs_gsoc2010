#include <QSqlQuery>
#include <QSqlRecord>
#include <QScriptValue>
#include <QScriptEngine>
#include <QVariant>
#include <kdemacros.h>
#include "../../KTextPluginNativeBridge.h"

class KDE_EXPORT SqlPlugin : public Plugin {
  public:
    SqlPlugin(QObject* parent = 0) : Plugin(parent) {}
    bool createSQLiteConnection(QString path);
    bool createMySQLConnection();
    bool createPostgresConnection();
    bool createOracleConnection();
    QScriptValue query(QString _query);
    QVariant getLastInsert();
  private:
    QVariant lastInsert;
    QSqlDatabase* db;
    QScriptEngine* m_pEngine;
};