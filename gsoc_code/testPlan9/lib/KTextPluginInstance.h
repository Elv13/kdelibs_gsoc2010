#ifndef TESTSCRIPTOBJECT_H
#define TESTSCRIPTOBJECT_H
//
#include <QObject>
#include <QScriptValue>
#include <QScriptable>
#include <QScriptEngine>
#include <QMessageBox>
#include <QFile>
#include "KTextEdit2.h"
#include <KMenu>
#include <KAction>
#include <QMap>

class QScriptEngine;



class KTextPluginInstance : public QObject
{
  Q_OBJECT
  Q_ENUMS(KInsertPolicy)
  
  public:
    KTextPluginInstance( QScriptEngine *pEngine, KTextEdit2* _textEditor, QObject *parent =0);
    void runScript(const QString& strProgram);
    
    enum KInsertPolicy { //Need to be explicit because JavaScript use them too
      InsertAfterCursor =1,
      InsertBeforeCursor =2,
      InsertAtLineBeginning =3,
      InsertAtDocBeginning =4,
      ReplaceSelection =5,
      ReplaceLine =6,
      ReplaceDocument=7,
      InsertBeforeSelection = 8
    };
    
  signals:
    void sequenceDetected(QString);
    void regExMatchFound(QString regEx);
    void patternFound(uint);
    void newContextMenu(int selectionLenght);

  public slots:
    void debug(QVariant variant);
    void insertText(QString text, KInsertPolicy policy = InsertBeforeCursor);
    void insertRichText(QString text, KInsertPolicy policy = InsertBeforeCursor);
    void removeCharacters(int _length);
    QString getCurrentDocumentPath();
    QString getCurrentLine();
    uint getCurrentCursorPos();
    QString getSelection();
    void getSelectionLines(QString objectName);
    QString getDocumentText();
    QStringList getDocumentLines();
    void patternTyped(uint code);
    
    void registerRegEx(QString regEx);
    void registerWatchListItem(QString text, QString function);
    
    bool addMenuTitle(QString title);
    bool addMenuItem(QString objectName, QString name);
    bool addSubMenu(QString name, QVariantMap actions);
    
    int exec(QString command);

    
    //Plugin information
    void category(QString _category);
    void name(QString _name);
    void version(QString _version);
    void about(QString _about);
    void author(QString _author);
    void website(QString _website);
    void documentation_url(QString _documentation_url);
    
  private slots:
    void menuRequest(QString selection, KMenu* menu);
    void disableMenu();
    
  private:
    QScriptEngine *m_pEngine;
    QScriptValue m_thisObject;
    KTextEdit2* m_textEdit;
    KMenu* m_menu;
    QAction* m_menuIndex;
    QStringList m_registeredRegEx;
    static const char* scriptPrefix;
    QHash<uint,QString> m_watchFuntionLink;
    
    QString m_category;
    QString m_name;
    QString m_version;
    QString m_about;
    QString m_author;
    QString m_website;
    QString m_documentation_url;
};
#endif