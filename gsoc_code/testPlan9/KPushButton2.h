#include <QToolButton>
#include <QDebug>
#include <QClipboard>

#ifndef KPUSHBUTTON2
#define KPUSHBUTTON2
class KPushButton2 : public QToolButton {
  Q_OBJECT
  public:
    KPushButton2(QWidget* parent);
  protected:
    void mouseReleaseEvent(QMouseEvent* event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    //void mousePressEvent(QMouseEvent* event);
    //void mouseDoubleClickEvent(QMouseEvent* event);
  private:
    QClipboard* buffer;
  signals:
    void textDropped(QString);
};
#endif