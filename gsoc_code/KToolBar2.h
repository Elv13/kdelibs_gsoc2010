//#include <KToolBar>
#include "/home/kde-devel/kde/src/kdelibs/kdeui/widgets/ktoolbar.h"
#include "KActionArg.h"
#include "KPushButton2.h"

#ifndef KTOOLBAR2
#define KTOOLBAR2
class KToolBar2 : public KToolBar {
  public:
    KToolBar2(QWidget* parent);
    KToolBar2(const QString &objectName, QWidget *parent, bool readConfig=true);
    void addAction(KArgAction* action);
    void addAction(KAction* action);
};
#endif