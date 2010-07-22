#ifndef H_TEST_KROSS1
#define H_TEST_KROSS1

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantList>

class TestKross1 : public QObject 
{
  Q_OBJECT
  
  Q_PROPERTY(bool boolProperty READ boolProperty WRITE setBoolProperty)
  Q_PROPERTY(int intProperty READ intProperty WRITE setIntProperty)
  Q_PROPERTY(double doubleProperty READ doubleProperty WRITE setDoubleProperty)
  Q_PROPERTY(QString stringProperty READ stringProperty WRITE setStringProperty)
  Q_PROPERTY(QStringList stringListProperty READ stringListProperty WRITE setStringListProperty)
  Q_PROPERTY(QVariantList listProperty READ listProperty WRITE setListProperty)
	
	
  public:
    TestKross1(QObject* parent);
    
  private:
    bool m_boolproperty;
    bool boolProperty() const { return m_boolproperty; }
    void setBoolProperty(bool prop) { m_boolproperty = prop; }

    int m_intproperty;
    int intProperty() const { return m_intproperty; }
    void setIntProperty(int prop) { m_intproperty = prop + 10; }

    double m_doubleproperty;
    double doubleProperty() const { return m_doubleproperty; }
    void setDoubleProperty(double prop) { m_doubleproperty = prop; }

    QString m_stringproperty;
    QString stringProperty() const { return m_stringproperty; }
    void setStringProperty(QString prop) { m_stringproperty = prop; }

    QStringList m_stringlistproperty;
    QStringList stringListProperty() const { return m_stringlistproperty; }
    void setStringListProperty(QStringList prop) { m_stringlistproperty = prop; }

    QVariantList m_listproperty;
    QVariantList listProperty() const { return m_listproperty; }
    void setListProperty(QVariantList prop) { m_listproperty = prop; }
    
    
};
#endif