/* This file is part of the KDE libraries
   Copyright (C) 2010 Emmanuel Lepage Vallee <elv1313@gmail.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "ktoolbox.h"
#include "ktoolbutton.h"

#include <QFrame>
#include <Qt>

#include "kmessagebox.h"

class KToolBoxPrivate {
  public:
    KToolBoxPrivate();
    QString title;
    QString action;
    QString separator;
    
    QString attrLayout;
    QString attrPosition;
    
    QString layoutAuto;
    QString layoutH;
    QString layoutV;
};


KToolBoxPrivate::KToolBoxPrivate() {
  title = "text";
  action = "action";
  separator = "separator";
  
  attrLayout = "layout";
  attrPosition = "position";
  
  layoutAuto = "auto";
  layoutH = "horizontal";
  layoutV = "vertical";
}


KToolBox::KToolBox(QWidget* parent) : QDockWidget(parent) {
  d = new KToolBoxPrivate();
  QWidget* mainWidget = new QWidget(this);
  setWidget(mainWidget);
  m_layout = new QHBoxLayout(mainWidget);
}

void KToolBox::loadState(const QDomElement &element) {
  QMainWindow *mw = mainWindow();
  if (!mw)
    return;
  
  if (!(element.hasAttribute( "position" )) || (element.attribute("position") == "left"))
    mw->addDockWidget(Qt::LeftDockWidgetArea,this);
  else if (element.attribute(d->attrPosition) == "right")
    mw->addDockWidget(Qt::RightDockWidgetArea,this);
  else if (element.attribute(d->attrPosition) == "top")
    mw->addDockWidget(Qt::TopDockWidgetArea,this);
  else if (element.attribute(d->attrPosition) == "bottom")
    mw->addDockWidget(Qt::BottomDockWidgetArea,this);
  
  QString boxLayout = element.attribute(d->attrLayout);
  if (boxLayout == d->layoutH)
    layout = KToolBox::Horizontal;
  else if (boxLayout == d->layoutV)
    layout = KToolBox::Vertical;
  else
    layout = KToolBox::Auto;
  
//   for (uint i = 0; i < element.childNodes().length();i++) {
//     KMessageBox::questionYesNo(this, "test");
//     QDomElement child = element.childNodes().at(i).toElement();
//     if (!child.isNull()) {
//       const QString tagName = child.tagName().toLower();
//       
//       if (tagName == d->title) {
// 	setWindowTitle(child.text());
//       }
//       else if (tagName == d->action) {
// 	//addAction();
// 	
//       }
//       else if (tagName == d->separator) {
// 	QFrame* line = new QFrame(this);
//         line->setObjectName(QString::fromUtf8("line"));
//         line->setGeometry(QRect(120, 130, 118, 3));
//         line->setFrameShape(QFrame::HLine);
//         line->setFrameShadow(QFrame::Sunken);
// 	m_layout->addWidget(line);
//       }
//     }
//   }
}

void KToolBox::insertAction (QAction* before, KAction* action, QString style)
{
  if (style == "alongside")
    insertAction(before,action,Qt::ToolButtonTextBesideIcon);
  else if (style == "under")
    insertAction(before,action,Qt::ToolButtonTextUnderIcon);
  else if (style == "icon")
    insertAction(before,action,Qt::ToolButtonIconOnly);
  else if (style == "text")
    insertAction(before,action,Qt::ToolButtonTextOnly);
  else
    insertAction(before,action/*,toolButtonStyle()*/);
}

void KToolBox::insertAction (QAction* before, KAction* action)
{
  insertAction(before,action,Qt::ToolButtonIconOnly);
}

void KToolBox::insertAction (QAction* before, KAction* action, Qt::ToolButtonStyle style)
{
  KToolButton* button = new KToolButton();
  button->setText(action->text()); 
  button->setIcon(action->icon()); 
  button->setToolButtonStyle(style);
  m_layout->addWidget(button);
  
  connect(button, SIGNAL(mimeDropped(const QMimeData*)), action, SLOT(dataTrigger(const QMimeData*)));
  connect(button, SIGNAL(clicked(bool)), action, SLOT(setChecked(bool)));
}

void KToolBox::addAction(KAction* action)
{
  insertAction(0,action);
}

void KToolBox::addAction(KAction* action, Qt::ToolButtonStyle style)
{
  insertAction(0,action,style);
}

KMainWindow * KToolBox::mainWindow() const
{
  return qobject_cast<KMainWindow*>(const_cast<QObject*>(parent()));
}
// void KToolBox::addAction(KAction* action) {
//   
// }