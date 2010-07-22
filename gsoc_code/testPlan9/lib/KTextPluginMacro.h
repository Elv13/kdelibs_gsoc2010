#include <kdemacros.h>
#include <KPluginFactory>
#include <KPluginLoader>
 
#define TEXTEDITOR_PLUGIN_EXPORT( c ) \
  K_PLUGIN_FACTORY( TextEditorFactory, registerPlugin< c >(); ) \
  K_EXPORT_PLUGIN( TextEditorFactory("c") )
  
  