#include "TestNative.h"

TestNative::TestNative(QObject *parent) : Plugin(parent)
{
  
}

TestNative::~TestNative()
{
  
}

QStringList TestNative::provide()
{
  QStringList aList;
  aList << "test1" << "test2" << "test3";
  return aList;
}