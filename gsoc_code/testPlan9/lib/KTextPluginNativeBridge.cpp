#include "KTextPluginNativeBridge.h"
#include <KTextEdit>
 
class Plugin::PluginPrivate {
 
public:
    PluginPrivate(Plugin *q):
                  q(q),
                  m_editor(0){}
 
    Plugin *q;
    KTextEdit *m_editor;
};
 
Plugin::Plugin(QObject *parent) : QObject(parent),
                                  d(new PluginPrivate(this))
{}
 
Plugin::~Plugin()
{
    delete d; 
}
 
// KTextEdit* Plugin::editorInterface()
// {
//     return d->m_editor;
// }
//  
// void Plugin::setEditorInterface(KTextEdit *editor)
// {
//     d->m_editor = editor;
// }

QScriptValue Plugin::qscript_call(QWidget *parent)
{
  //QMessageBox * const iface = new Wrapper_QMessageBox(parent);
  //return engine()->newQObject(iface, QScriptEngine::AutoOwnership); 
}