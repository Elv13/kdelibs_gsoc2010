#include "KToolBar2.h"
#include <QWidget>

KToolBar2::KToolBar2(QWidget* parent) : KToolBar(parent) {
  //setStyleSheet("background-color:red");
}

KToolBar2::KToolBar2(const QString &objectName, QWidget *parent, bool  readConfig) : KToolBar(objectName, parent, readConfig) {
 // setStyleSheet("background-color:red");
}

void KToolBar2::addAction(KArgAction* action) {
  KPushButton2* aPushButton = new KPushButton2(this);
  aPushButton->setText(action->text());
  aPushButton->setIcon(action->icon());
  aPushButton->setToolButtonStyle(toolButtonStyle());
  addWidget(aPushButton);
  connect(aPushButton, SIGNAL(textDropped(QString)), action, SLOT(toggle(QString)));
  //return aPushButton;
}

void KToolBar2::addAction(KAction* action) {
  KToolBar::addAction(action);
}