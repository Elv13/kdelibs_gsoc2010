#include "mainwindow.h"
 
#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <QGridLayout>
#include <QFile>
#include <QScriptEngine>

//#include "copy/kedittoolbar.h"
#include "lib/KTextPluginManager.h"
 
MainWindow::MainWindow(QWidget *parent, QString windowTitle)
    : KMainWindow(parent)
{
  setWindowTitle(windowTitle);
  m_textArea = new KTextEdit2(this);
  new SyntaxHighlighter(m_textArea);
  QWidget* main = new QWidget(this);
  QGridLayout* mainLayout = new QGridLayout(main);
  mainLayout->addWidget(m_textArea,0,1);
  
  setCentralWidget(main);
 
  setupActions();
  
//   QScriptEngine *pEngine = new QScriptEngine(this);
//   KTextPlugin2* aScript = new KTextPlugin2(pEngine, m_textArea, this);
//   aScript->runScript("");
  KTextPluginManager* aManager = new KTextPluginManager(this,m_textArea);
  //aManager->addPlugin("/home/kde-devel/kde/src/testPlan9/testScript.js");
  aManager->addPlugin("/home/lepagee/dev/testPlan9/plugin/bracket.js");
  
  //KEditToolBar* anEditor = new KEditToolBar(this);
  //setupGUI();
}
 
void MainWindow::setupActions()
{
  
  m_testToolBar = new KToolBar2(this);
  
  KArgAction* findAction = new KArgAction(this);
  findAction->setText("Find");
  findAction->setIcon(KIcon("edit-find"));
  m_actionCollection["Find"] = findAction;

  connect(findAction, SIGNAL(toggled(QString)),
          this, SLOT(find(QString)));
  
  KArgAction* newAction = new KArgAction(this);
  newAction->setText("New");
  newAction->setIcon(KIcon("document-new"));
  m_actionCollection["New"] = newAction;
  
  connect(newAction, SIGNAL(toggled(QString)),
          this, SLOT(newDoc(QString)));
  
  KArgAction* openAction = new KArgAction(this);
  openAction->setText("Open");
  openAction->setIcon(KIcon("document-open"));
  m_actionCollection["Open"] = openAction;
  
  connect(openAction, SIGNAL(toggled(QString)),
          this, SLOT(open(QString)));
  //actionCollection()->addAction("find", findAction);
//   
  m_testToolBar->addAction(newAction);
  m_testToolBar->addAction(openAction);
  m_testToolBar->addAction(findAction);
  
  connect(m_textArea, SIGNAL(actionTriggered(QString, QString)), this, SLOT(matchAction(QString,QString)));
  
  
  addToolBar(Qt::TopToolBarArea,m_testToolBar);
  
  //setupGUI(Default, "testplan9ui.rc");
}

void MainWindow::find(QString text) {
  m_textArea->find(text);
}

void MainWindow::open(QString path) {
  MainWindow* aNewMainWindow = new MainWindow(this, path);
  aNewMainWindow->show();
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      return;

  aNewMainWindow->m_textArea->setText(file.readAll());
  file.close();
}

void MainWindow::newDoc(QString text) {
  MainWindow* aNewMainWindow = new MainWindow(this);
  aNewMainWindow->show();
  aNewMainWindow->m_textArea->setText(text);
}

//This function would go in KActionCollection
void MainWindow::matchAction(QString name, QString arg) {
  qDebug() << "I am her3 " << name;
  if (m_actionCollection.find(name) != m_actionCollection.end()) {
    qDebug() << "I am her4";
    m_actionCollection[name]->toggle(arg);
  }
}