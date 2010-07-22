#include "KPushButton2.h"
#include <QMouseEvent>
#include <QApplication>

KPushButton2::KPushButton2(QWidget* parent) : QToolButton(parent) {
  buffer = QApplication::clipboard();
  setCheckable(false);
  setAcceptDrops(true);
}

void KPushButton2::mouseReleaseEvent(QMouseEvent* event) {
  qDebug() << event->buttons();
  if (event->button() == Qt::MidButton) {
    emit textDropped(buffer->text(QClipboard::Selection));
    qDebug() << buffer->text(QClipboard::Selection);
  }
}

void KPushButton2::dragEnterEvent(QDragEnterEvent *event) {
  //if (event->mimeData()->hasFormat("text/plain"))
  //TODO implement a way to filter unwanter mimetypes
  event->acceptProposedAction();
}

void KPushButton2::dropEvent(QDropEvent *event) {
  qDebug() << "Available format: " << event->mimeData()->formats();
  if (event->mimeData()->hasFormat("text/plain")) {
    emit textDropped(buffer->text(QClipboard::Selection));
  }
}

// void KPushButton2::mousePressEvent(QMouseEvent* event) {
//   qDebug() << "I am here2";
// }
// 
// void KPushButton2::mouseDoubleClickEvent(QMouseEvent* event) {
//   qDebug() << "I am here3";
// }