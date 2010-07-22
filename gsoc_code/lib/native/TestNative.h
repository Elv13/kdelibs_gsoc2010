#ifndef h_TESTNATIVE
#define h_TESTNATIVE

#include "../KTextPluginNativeBridge.h"

class TestNative : public Plugin
{
  public:
    TestNative(QObject *parent);
    virtual ~TestNative();
    virtual QStringList provide();
};

#endif