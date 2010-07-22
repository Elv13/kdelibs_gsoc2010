#include "KTextPluginInstance.h"
#include <KDebug>
#include <QTextStream>

const char* KTextPluginInstance::scriptPrefix = "var KInsertPolicy = new Object(); \
					  KInsertPolicy.InsertAfterCursor =1;\
					  KInsertPolicy.InsertBeforeCursor =2;\
					  KInsertPolicy.InsertAtLineBeginning =3;\
					  KInsertPolicy.InsertAtDocBeginning =4;\
					  KInsertPolicy.ReplaceSelection =5;\
					  KInsertPolicy.ReplaceLine =6;\
					  KInsertPolicy.ReplaceDocument=7;\
					  KInsertPolicy.InsertBeforeSelection=8;\
					  ";

KTextPluginInstance::KTextPluginInstance(  QScriptEngine *pEngine, KTextEdit2* _textEditor, QObject* parent) : QObject(parent), m_pEngine(pEngine), m_textEdit(_textEditor), m_menu(0) {
  m_thisObject = m_pEngine->newQObject(this);
  connect(m_textEdit, SIGNAL(contextMenuRequested(QString, KMenu*)), this, SLOT(menuRequest(QString, KMenu*)));
  connect(m_textEdit, SIGNAL(patternTyped(uint)), this, SLOT(patternTyped(uint)));
}

void KTextPluginInstance::runScript(const QString &strAppName) {
  QFile file(strAppName);//strAppName + ".js");

  if (! file.exists()) {
    QMessageBox::critical(0, "Error", "Could not find program file!");
    return;
  }

  if (! file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::critical(0, "Error", "Could not open program file!");
    return;
  }

  QString strProgram = scriptPrefix + file.readAll();

  // do static check so far of code:
  if (! m_pEngine->canEvaluate(strProgram) ) {
    QMessageBox::critical(0, "Error", "canEvaluate returned false!");
    return;
  }

  // actually do the eval:
  m_pEngine->evaluate(strProgram);

  // uncaught exception?
  if (m_pEngine->hasUncaughtException()) {
    QScriptValue exception = m_pEngine->uncaughtException();
    QMessageBox::critical(0, "Script error", QString("Script threw an uncaught exception: ") + exception.toString());
    return;
  }

  QScriptValue createFunc = m_pEngine->evaluate("create");

  if (m_pEngine->hasUncaughtException()) {
    QScriptValue exception = m_pEngine->uncaughtException();
    QMessageBox::critical(0, "Script error", QString("Script threw an uncaught exception while looking for create func: ") + exception.toString());
    return;
  }

  if (!createFunc.isFunction()) {
    QMessageBox::critical(0, "Script Error", "createFunc is not a function!");
  }

  createFunc.call(m_thisObject);

  if (m_pEngine->hasUncaughtException()) {
    QScriptValue exception = m_pEngine->uncaughtException();
    QMessageBox::critical(0, "Script error", QString("Script threw an uncaught exception while looking for create func: ") + exception.toString());
    return;
  }
}


void KTextPluginInstance::debug(QVariant variant) 
{ 
  kDebug() << variant;
}
/*InsertAfterCursor, --
  InsertBeforeCursor, --
  InsertAtLineBeginning, --
  InsertAtDocBeginning, --
  ReplaceSelection, --
  ReplaceLine, --
  Replacedocument*/
void KTextPluginInstance::insertText(QString text, KInsertPolicy policy)
{
  qDebug() << "Replace Text type:" << policy;
  if (policy == ReplaceSelection) {
    m_textEdit->insertPlainText(text);
    return;
  }
  else {
    QTextCursor cur = m_textEdit->textCursor();
    //QStringList lineList = cur.selectedText().replace(QChar(0x2029),QString("\n")).split("\n"); 
    if (policy == InsertAfterCursor) {
      int curPos = cur.selectionEnd();
      cur.insertText(text);
      cur.setPosition(curPos);
    }
    else if (policy == InsertBeforeCursor) {
      int curPos = cur.selectionEnd();
      cur.setPosition(curPos);
      cur.insertText(text);
      cur.movePosition(QTextCursor::Right,QTextCursor::MoveAnchor,text.size());
    }
    else if (policy == InsertBeforeSelection) {
      int curPos = cur.selectionStart();
      cur.setPosition(curPos);
      cur.insertText(text);
      cur.movePosition(QTextCursor::Right,QTextCursor::MoveAnchor,text.size());
    }
    else if (policy == InsertAtLineBeginning) {
      int curPos = cur.selectionEnd();
      cur.movePosition(QTextCursor::StartOfLine);
      cur.insertText(text);
      cur.setPosition(curPos+text.size());
    }
    else if (policy == InsertAtDocBeginning) {
      int curPos = cur.selectionEnd();
      m_textEdit->setHtml(text+m_textEdit->toHtml());
      cur.setPosition(curPos+text.size());
    }
    else if (policy == ReplaceLine) {
      cur.select(QTextCursor::LineUnderCursor);
      cur.removeSelectedText();
      cur.insertText(text);
    }
    else if (policy == ReplaceDocument) {
      m_textEdit->setPlainText(text);
    }
    m_textEdit->setTextCursor(cur);
  }
}

void KTextPluginInstance::removeCharacters(int _length)
{
  qDebug() << "\n\n\n\n\nwerwerwer:" << _length << "\n\n\n\n\n";
  QTextCursor cur = m_textEdit->textCursor();
  int curPos = cur.selectionEnd();
  if (_length > 0) {
    for (int i=0;i<_length;i++)
      cur.deleteChar();
  }
  else if (_length < 0) {
   for (int i=-_length;i>0;i--)
     cur.deletePreviousChar();
  }
  m_textEdit->setTextCursor(cur);
}

void KTextPluginInstance::insertRichText(QString text, KInsertPolicy policy)
{
  m_textEdit->insertHtml(text);
}

QString KTextPluginInstance::getCurrentDocumentPath()
{
  //TODO
}

QString KTextPluginInstance::getCurrentLine()
{
  QTextCursor cur = m_textEdit->textCursor();
  int curPos = cur.selectionEnd();
  cur.select(QTextCursor::LineUnderCursor);
  QString toReturn = cur.selectedText();
  return toReturn;
}

uint KTextPluginInstance::getCurrentCursorPos()
{
  QTextCursor cur = m_textEdit->textCursor();
  return cur.selectionEnd();
}

QString KTextPluginInstance::getSelection()
{
  QTextCursor cur = m_textEdit->textCursor();
  return cur.selectedText();
}

void KTextPluginInstance::getSelectionLines(QString objectName)
{
  QTextCursor cur = m_textEdit->textCursor();
  QStringList lineList = cur.selectedText().replace(QChar(0x2029),QString("\n")).split("\n"); //Both can exist
  
  QScriptValue objectValue = m_pEngine->newArray(lineList.size());
  for (int i =0; i < lineList.size();i++) {
    objectValue.setProperty(i,lineList[i]);qDebug() <<"Add line:" << lineList[i];
  }
  m_pEngine->globalObject().setProperty(objectName, objectValue);
}

QString KTextPluginInstance::getDocumentText()
{
  return m_textEdit->toPlainText();
}

QStringList KTextPluginInstance::getDocumentLines()
{
  return m_textEdit->toPlainText().split("\n");
}

void KTextPluginInstance::registerRegEx(QString regEx)
{
  m_registeredRegEx << regEx;
}

void KTextPluginInstance::registerWatchListItem(QString text, QString function)
{
  m_watchFuntionLink[m_textEdit->registerWatchListItem(text)] = function;
}

void KTextPluginInstance::patternTyped(uint code)
{
  qDebug() << "I am here" << code << m_watchFuntionLink[code];
  QScriptValue function = m_pEngine->globalObject().property(m_watchFuntionLink[code]);
  function.call(m_thisObject);
}

int KTextPluginInstance::exec(QString command) 
{
  qDebug() << "Would exec: " << command;
  return 0;
}

void KTextPluginInstance::menuRequest(QString selection, KMenu* menu)
{
  emit newContextMenu(selection.size());
  qDebug() << "Ready to alter menu";
  
  connect(menu, SIGNAL(aboutToHide()), this, SLOT(disableMenu()));
  m_menu = menu;
  m_menuIndex = 0;
  
  m_menu->addTitle("Menu real content");
  
  foreach (QString aRegex, m_registeredRegEx) {
    QRegExp rx(aRegex);
    rx.setPatternSyntax(QRegExp::RegExp);
    if (rx.exactMatch(selection)) {
      emit regExMatchFound(aRegex);
    }
  }
}

void KTextPluginInstance::disableMenu()
{
  m_menu = NULL;
}

bool KTextPluginInstance::addMenuTitle(QString title)
{
  if (m_menu) {
    if (!m_menuIndex) {
      m_menu->addSeparator();
    }
    m_menuIndex = m_menu->addTitle(title);
    return true;
  }
  return false;
}

bool KTextPluginInstance::addMenuItem(QString objectName, QString name)
{
  if (m_menu) {
    if (!m_menuIndex) {
      m_menu->addSeparator();
    }
    m_menuIndex = m_menu->addAction(name);
    QScriptValue objectValue = m_pEngine->newQObject(m_menuIndex);
    m_pEngine->globalObject().setProperty(objectName, objectValue);
    
    //QScriptValue function = m_pEngine->evaluate("function changeDate() { this.insertText(\"]werwerwre]]\",KInsertPolicy.InsertAfterCursor); }");
    //function.call(m_thisObject); //work
    //qScriptConnect(m_textEdit, SIGNAL(returnPresrsed()), m_pEngine->globalObject(), function); //does not work
    return true;
  }
  return false;
}

bool KTextPluginInstance::addSubMenu(QString name, QVariantMap actions)
{
  if (m_menu) {
    
    if (!m_menuIndex) {
      m_menu->addSeparator();
    }
    QMap<QString,QVariant> subMenuActions;
    QMenu* subMenu = m_menu->addMenu(name);
    foreach (QVariant actionName, actions) {
      QScriptValue objectValue = m_pEngine->newQObject(subMenu->addAction(actionName.toString()));
      m_pEngine->globalObject().setProperty(actions.key(actionName), objectValue);
    }
    return true;
  }
  return false;
}

void KTextPluginInstance::category(QString _category)
{
  m_category = _category;
}

void KTextPluginInstance::name(QString _name)
{
  m_name = _name;
}

void KTextPluginInstance::version(QString _version)
{
  m_version = _version;
}

void KTextPluginInstance::about(QString _about)
{
  m_about = m_about;
}

void KTextPluginInstance::author(QString _author)
{
  m_author = _author;
}

void KTextPluginInstance::website(QString _website)
{
  m_website = _website;
}

void KTextPluginInstance::documentation_url(QString _documentation_url)
{
  m_documentation_url = _documentation_url;
}
