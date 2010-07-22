#include "mainwindow.h"
 
#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <QGridLayout>
#include <QFile>
#include <QScriptEngine>
#include <kross/core/manager.h>
#include <kross/core/action.h>

//#include "copy/kedittoolbar.h"
#include "lib/KTextPluginManager.h"
#include "lib/native2/kate/kate.h"
 
MainWindow::MainWindow(QWidget *parent, QString windowTitle)
    : KMainWindow(parent)
{
  setWindowTitle(windowTitle);
  m_textArea = new KTextEdit2(this);
  new SyntaxHighlighter(m_textArea);
  QWidget* main = new QWidget(this);
  QGridLayout* mainLayout = new QGridLayout(main);
  mainLayout->addWidget(m_textArea,0,0);
  
  setCentralWidget(main);
 
  setupActions();
  
  cmbInterpreters = new QComboBox (this);
  cmbInterpreters->addItem("Choose Interpreter", "");
  mainLayout->addWidget(cmbInterpreters,1,0);
  
  foreach(QString s, Kross::Manager::self().interpreters())
    cmbInterpreters->addItem(s);
  
  lblHello = new QLabel("Hello", this);
  mainLayout->addWidget(lblHello,2,0);
  
//   QScriptEngine *pEngine = new QScriptEngine(this);
//   KTextPlugin2* aScript = new KTextPlugin2(pEngine, m_textArea, this);
//   aScript->runScript("");
  KTextPluginManager* aManager = new KTextPluginManager(this,m_textArea);
  Plugin* katePlugin = new KatePlugin();
  aManager->addNativePlugin(katePlugin);
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

void MainWindow::interpreterActivated(const QString &strSelectedInterpreter)
{
  if(strSelectedInterpreter.isEmpty())
  {
    // if no interpreter was selected, we display nothing.
    lblHello->setText("-");
    return;
  }
 
  // Now let's create a Kross::Action instance which will act
  // as container for our script. You are also able to cache
  // that action, manipulate it on demand or execute it multiple
  // times.
  Kross::Action action(this, "MyScript");
  // Now let's set the scripting code that should be executed
  // depending on the choosen interpreter. You are also able to
  // use action.setFile("/path/scriptfile") here to execute
  // an external scriptfile, as shown later in this tutorial.
  if(strSelectedInterpreter == "python")
    action.setCode("import MyLabel\nMyLabel.text = 'Hello from python!'");
  else if(strSelectedInterpreter == "ruby")
    action.setCode("require 'MyLabel'\nMyLabel.text = 'Hello from ruby!'");
  else if(strSelectedInterpreter == "javascript")
    action.setCode("MyLabel.setText('Hello from javascript!')");
  else
    return;
 
  // Set the name of the interpreter that should be used to
  // evaluate the scripting code above. It's not needed to set
  // it explicitly if we defined an external scripting file via
  // action.setFile() since then Kross will determinate the right
  // one. But since we set the scripting code above manually by using
  // action.setCode() we need to define explicitly what interpreter
  // should be used.
  action.setInterpreter(strSelectedInterpreter);
 
  // Now let's add the QLabel instance to let the scripting code
  // access it.
  action.addObject(lblHello, "MyLabel");
 
  // Finally execute the scripting code.
  action.trigger();
}