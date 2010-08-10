#include "kshortcutsdialog_p.h"

#include <QGridLayout>
#include <QRadioButton>
#include <QLabel>
#include <kpushbutton.h>
#include <kgesture.h>

GestureEditWidget::GestureEditWidget(QWidget *viewport) : TabConnectedWidget(viewport),m_currentX(0),m_currentY(0)
{
	m_currentGesture = new QLabel(this);
  
        m_left = new KPushButton(this);
	m_left->setText("Left");
        m_right = new KPushButton(this);
	m_right->setText("Right");
        m_up = new KPushButton(this);
	m_up->setText("Up");
        m_down = new KPushButton(this);
	m_down->setText("Down");
	m_clear = new KPushButton(this);
	m_clear->setText("Clear");
	m_ok = new KPushButton(this);
	m_ok->setText("OK");
	
	QGridLayout* aLayout = new QGridLayout(this);
	
	aLayout->addWidget(m_currentGesture,0,0,1,5);
	aLayout->addWidget(m_left,1,0);
	aLayout->addWidget(m_right,1,1);
	aLayout->addWidget(m_up,1,2);
	aLayout->addWidget(m_down,1,3);
	aLayout->addWidget(m_clear,1,4);
	aLayout->addWidget(m_ok,1,5);
	
	m_shape << QPoint(0,0);
	connect(m_left,SIGNAL(clicked()),this,SLOT(leftClicked()));
	connect(m_right,SIGNAL(clicked()),this,SLOT(rightClicked()));
	connect(m_up,SIGNAL(clicked()),this,SLOT(upClicked()));
	connect(m_down,SIGNAL(clicked()),this,SLOT(downClicked()));
	connect(m_clear,SIGNAL(clicked()),this,SLOT(clearClicked()));
	connect(m_ok,SIGNAL(clicked()),this,SLOT(okClicked()));
	
}

void GestureEditWidget::leftClicked()
{
  m_currentGesture->setText(m_currentGesture->text()+"L");
  m_shape << QPoint(m_currentX-20,m_currentY);
}

void GestureEditWidget::rightClicked()
{
  m_currentGesture->setText(m_currentGesture->text()+"R");
  m_shape << QPoint(m_currentX+20,m_currentY);
}

void GestureEditWidget::upClicked()
{
  m_currentGesture->setText(m_currentGesture->text()+"U");
  m_shape << QPoint(m_currentX,m_currentY+20);
}

void GestureEditWidget::downClicked()
{
  m_currentGesture->setText(m_currentGesture->text()+"D");
  m_shape << QPoint(m_currentX,m_currentY-20);
}

void GestureEditWidget::clearClicked()
{
  m_currentGesture->setText("");
  m_shape.clear();
}

void GestureEditWidget::okClicked()
{
  KShapeGesture* gesture = new KShapeGesture(m_shape);
  gesture->setShapeName(m_currentGesture->text());
  emit shapeGestureChanged(*gesture);
}