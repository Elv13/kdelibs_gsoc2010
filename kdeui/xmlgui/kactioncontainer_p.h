#ifndef KACTIONCONTAINER_H
#define KACTIONCONTAINER_H

#include <kaction.h>

class KActionContainer {
  public:
    KActionContainer() {}
    virtual void addAction(KAction* action, Qt::ToolButtonStyle style) = 0;
    virtual void addAction(KAction* action) = 0;
    virtual void insertAction(QAction* before, KAction* action, Qt::ToolButtonStyle style) = 0;
    virtual void insertAction(QAction* before, KAction* action, QString style) = 0;
    virtual void insertAction(QAction* before, KAction* action) = 0;
    virtual ~KActionContainer() {}
};

#endif //KACTIONCONTAINER_H