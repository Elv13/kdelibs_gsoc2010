#ifndef h_PLUGIN
#define h_PLUGIN

#include <kdemacros.h>
#include <kxmlguiclient.h>
#include <QObject>
#include <QScriptable>
#include <QScriptValue>
 
//class KTextEdit;
 
class KDE_EXPORT Plugin : public QObject , protected QScriptable
{
    Q_OBJECT
 
    public:
        Plugin(QObject *parent);
	~Plugin();
        virtual QStringList provide() = 0;
	//virtual 
 
    private:
        class PluginPrivate;
        PluginPrivate *d;
	
  public slots:
    QScriptValue qscript_call(QWidget *parent = 0);
};
#endif