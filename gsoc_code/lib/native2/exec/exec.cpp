#include "exec.h"

#include <kstandarddirs.h>
#include <KProcess>
#include <KRun>
#include <kservicetypetrader.h>
#include <KMimeTypeTrader>

bool ExecPlugin::exec(QString command, QStringList argv) {
  KProcess::execute(command,argv);
}

QString ExecPlugin::findExecByName(QString command) {
  return KStandardDirs::findExe(command);
}

QString ExecPlugin::findExecByMime(QString mime) {
   return KMimeTypeTrader::self()->preferredService(mime)->desktopEntryPath();
}

QScriptValue ExecPlugin::listExecByMime(QString mime) {
  KService::List executables = KMimeTypeTrader::self()->query(mime,"Application");
  QScriptValue aList = m_pEngine->newArray(executables.size());
  int i =0;
  foreach (KSharedPtr<KService> aService, executables) {
    aList.setProperty(i,aService->desktopEntryPath());
    i++;
  }
  return aList;
}

bool ExecPlugin::setMime(QString mime, QString application) {
  
}

QString ExecPlugin::getIcon(QString application) {
  
}

int ExecPlugin::getPid(QString application) {
  
}
