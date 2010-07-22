#include <QFile>
#include <QStringList>
#include <kdemacros.h>
#include "../../KTextPluginNativeBridge.h"

class ObjFile;

class KDE_EXPORT FilePlugin : public Plugin {
  public:
    FilePlugin(QObject* parent = 0) : Plugin(parent) {}
    ObjFile openFile(QString path, char type);
    bool closeFile(ObjFile file);
    ObjFile newFile(QString path, char type);
    QStringList scanDir(QString path);
    bool exists(QString path);
    bool removefile(QString path);
    bool copyFile(QString oldPath, QString newPath);
    bool moveFile(QString oldPath, QString newPath);
    //getTmpDir()
    //getPluginDataDir()
    //createTmpFile()
  private:
    
};

class ObjFile : public QObject {
  public:
    ObjFile(QObject* parent) : QObject(parent) {}
  public slots:
    ObjFile(QString path, char type);
    char readChar();
    QString readLine();
    QString readAll();
    QStringList readAllLines();
    bool write(char* content);
    bool append(QString content);
    int position();
    bool close();
  private:
    QFile m_file;
};