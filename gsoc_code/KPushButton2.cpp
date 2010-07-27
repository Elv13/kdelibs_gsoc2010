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

#include "ktoolbutton.h"
#include <QMouseEvent>
#include <QApplication>

KToolButton::KToolButton(QWidget* parent) : QToolButton(parent) {
  m_buffer = QApplication::clipboard();
  setCheckable(false);
  setAcceptDrops(true);
}

void KToolButton::mouseReleaseEvent(QMouseEvent* event) {
  qDebug() << event->buttons();
  if (event->button() == Qt::MidButton) {
    QMimeData* data = new QMimeData();
    data->setText(m_buffer->text(QClipboard::Selection));
    emit mimeDropped(data);
  }
}

void KToolButton::dragEnterEvent(QDragEnterEvent *event) {
  //TODO implement a way to filter unwanter mimetypes
  event->acceptProposedAction();
}

void KToolButton::dropEvent(QDropEvent *event) {
  qDebug() << "Available format: " << event->mimeData()->formats();
  //if (event->mimeData()->hasFormat("text/plain")) {
  //  emit textDropped(buffer->text(QClipboard::Selection));
  //}
  emit mimeDropped(event->mimeData());
}