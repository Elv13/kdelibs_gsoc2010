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

#ifndef KTOOLBOX_H
#define KTOOLBOX_H

#include <QDockWidget>
#include <QDomElement>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <kmainwindow.h>
#include "kactioncontainer_p.h"

class KToolBoxPrivate;


/**
 * @short Equivalent of a toolbar implemnted in a QDockWidget
 *
 * KToolButton is a class used to display a list of actions
 *
 * @author Emmanuel Lepage Vallee <elv1313@gmail.com>
 */
class KToolBox : public QDockWidget, public KActionContainer {
    Q_OBJECT
  public:
    /**
     * Constructs a KMenu.
     */
    KToolBox(QWidget* parent);
    
    /**
     * Read the XML and generate the layout accordingly
     * @param element An XML node containing informations about the layout and content of the toolbox
     */
  public:
    void loadState(const QDomElement &element);
    virtual void insertAction (QAction* before, KAction* action);
    virtual void insertAction (QAction* before, KAction* action, QString style);
    virtual void insertAction (QAction* before, KAction* action, Qt::ToolButtonStyle style);
    virtual void addAction(KAction* action);
    virtual void addAction(KAction* action, Qt::ToolButtonStyle style);
    enum KToolBoxLayout {
      Auto,
      Vertical,
      Horizontal
    };
  private:
    //class KToolBoxPrivate;
    KToolBoxLayout layout;
    KToolBoxPrivate* d;
    QHBoxLayout* m_layout;
    KMainWindow * mainWindow() const;
};

#endif //KTOOLBOX_H