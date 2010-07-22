#include <KAction>
//#include "/home/kde-devel/kde/src/kdelibs/kdeui/actions/kaction.h"
#ifndef KARGACTION
#define KARGACTION
class KArgAction : public KAction {
  Q_OBJECT
  public:
    KArgAction(QObject* parent) : KAction(parent) {setCheckable(false);}
  public slots:
    void toggle(QString text) {
      emit toggled(text);
    }
  signals:
    void toggled(QString);
};

#endif