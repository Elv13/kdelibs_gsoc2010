#include <KAction>
#include <QMimeData>
//#include "/home/kde-devel/kde/src/kdelibs/kdeui/actions/kaction.h"
#ifndef KARGACTION
#define KARGACTION
class KArgAction : public KAction {
  Q_OBJECT
  public:
    KArgAction(QObject* parent) : KAction(parent) {setCheckable(false);}
  public slots:
    void toggle(QMimeData &text) {
      emit toggled(text);
    }
    
    void toggle(QString text) {
      QMimeData data;
      data.setText(text);
      emit toggled(data);
    }
    
  signals:
    void toggled(QMimeData&);
};

#endif