#include <KTextEdit>
#include <QClipboard>
#include <KMenu>
#include <QMap>

#ifndef KTEXTEDIT2
#define KTEXTEDIT2

#include "ktextplugin_export.h"

//class KTextPlugin2;

typedef struct WatchString {
  ushort* string;
  uchar length;
} WatchString;

class LIBKTEXTPLUGIN_EXPORT KTextEdit2 : public KTextEdit {
  Q_OBJECT
  
  //friend class KTextPlugin2;
  
  public:
    KTextEdit2(QWidget* parent);
    ~KTextEdit2() {}
    uint registerWatchListItem(const QString item);
    
  protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void contextMenuEvent(QContextMenuEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);

  private:
    QClipboard* m_buffer;
    QList<WatchString*> m_watchList;
    //QStringList m_watchList;
    QMap<WatchString*, int> m_patternValue;
    ushort* m_cirularBuffer;
    uchar m_circularBufferStart;
    char m_circularBufferEnd;
    bool m_init;
    uint m_patternValueCounter;
    
  signals:
    void actionTriggered(QString);
    void actionTriggered(QString, QString);
    void contextMenuRequested(QString, KMenu*);
    void patternTyped(uint);
};
#endif