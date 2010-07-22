#include "sql.h"
#include <QDebug>

bool SqlPlugin::createSQLiteConnection(QString path) {
  db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
  db->setDatabaseName(path);
  qDebug() << (( db->open())? "Database corectly opened":"ERROR while opening the database "+path);
}

bool SqlPlugin::createMySQLConnection() {
  
}

bool SqlPlugin::createPostgresConnection() {
  
}

bool SqlPlugin::createOracleConnection() {
  
}

QScriptValue SqlPlugin::query(QString _query) {
  QSqlQuery query(query);
  query.exec();
  lastInsert = query.lastInsertId();
  QScriptValue rows = m_pEngine->newArray(query.size());
  int j =0;
  while (query.next()) {
    QScriptValue aRow = m_pEngine->newArray(query.record().count());
    for (int i =0; i < query.record().count();i++) {
      aRow.setProperty(i,query.value(i).toString());
    }
    rows.setProperty(j,aRow);
    j++;
  }
//   QScriptValue toReturn = m_pEngine->newArray(rows.count());
//   for (int i =0; i < aRow.count();i++) {
//     toReturn.setProperty(i,query.value(i));
//   }
  return rows;
}

QVariant SqlPlugin::getLastInsert() {
  return lastInsert;
}
