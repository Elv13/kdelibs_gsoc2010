#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KUrl>
#include <QDebug>

#include "mainwindow.h"

int main (int argc, char *argv[]) {
  KAboutData aboutData( "testplan9", "testplan9",
  ki18n("Kimberlite"), "0.0.9",
  ki18n("A complete environemnt to develop, manage and execute Unix scripts"),
  KAboutData::License_GPL,
  ki18n("Copyright (c) 2008 Emmanuel Lepage Vallee") );
  KCmdLineArgs::init( argc, argv, &aboutData );

  KCmdLineOptions options; 
  options.add("+[file]", ki18n("Document to open")); 
  KCmdLineArgs::addCmdLineOptions(options); 

  KApplication app;

  MainWindow* window = new MainWindow(0);
  window->show();
  
  KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

  return app.exec();
}
