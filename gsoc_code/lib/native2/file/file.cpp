#include "file.h"
#include <QFile>
#include <QDir>

ObjFile FilePlugin::openFile(QString path, char type) {
  QFile aFile(path);
  //return 
}

bool FilePlugin::closeFile(ObjFile file) {
  file.close();
}

ObjFile FilePlugin::newFile(QString path, char type) {
  openFile(path,'w');
  //return *(new ObjFile(path,'w'));
}

QStringList FilePlugin::scanDir(QString path) {
  QDir aDir(path);
  return aDir.entryList();
}

bool FilePlugin::removefile(QString path) {
  return QFile::remove(path);
}

bool FilePlugin::copyFile(QString oldPath, QString newPath) {
  return QFile::copy(oldPath,newPath);
}

bool FilePlugin::moveFile(QString oldPath, QString newPath) {
  bool toReturn = false;
  toReturn += !QFile::copy(oldPath,newPath);
  toReturn += !QFile::remove(oldPath);
  return !toReturn;
}

bool FilePlugin::exists(QString path) {
  return QFile::exists(path);
}

char ObjFile::readChar() {
  char aChar;
  m_file.getChar(&aChar);
  return aChar;
}

QString ObjFile::readLine() {
  return m_file.readLine();
}

QString ObjFile::readAll() {
  return m_file.readAll();
}

QStringList ObjFile::readAllLines() {
  QStringList toReturn;
  while (!m_file.atEnd()) {
    QByteArray line = m_file.readLine();
    toReturn << line;
  }
  return toReturn;
}

bool ObjFile::write(char* content) {
  m_file.write(content);
}

bool ObjFile::append(QString content) {
  //TODO
}

int ObjFile::position() {
  return m_file.pos();
}

bool ObjFile::close() {
  m_file.close();
}