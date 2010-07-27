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

#include <QToolButton>
#include <QDebug>
#include <QClipboard>

#ifndef KTOOLBUTTON_H
#define KTOOLBUTTON_H

/**
 * @short KDE variant of QToolButton
 *
 * KToolButton is a class used in toolbars instead of QToolButton and 
 * provide support for drag and drop
 *
 * @author Emmanuel Lepage Vallee <elv1313@gmail.com>
 */
class KToolButton : public QToolButton {
  Q_OBJECT
  public:
    /**
     * Constructs a KMenu.
     */
    explicit KToolButton(QWidget* parent = 0);
  protected:
    
    /**
     * Reimplementation of QWidget::mouseReleaseEvent
     * @param event The event passed when the action occur
     */
    void mouseReleaseEvent(QMouseEvent* event);
    
    /**
     * Reimplementation of QWidget::dropEvent
     * @param event The event passed when the action occur
     */
    void dropEvent(QDropEvent *event);
    
    /**
     * Reimplementation of QWidget::dragEnterEvent
     * @param event The event passed when the action occur
     */
    void dragEnterEvent(QDragEnterEvent *event);
  private:
    QClipboard* m_buffer;
  signals:
    /**
     * Emmited when data is dropped on the toolbutton using drag and drop of middle mouse button (Unix only)
     */
    void mimeDropped(const QMimeData*);
};
#endif //KTOOLBUTTON_H