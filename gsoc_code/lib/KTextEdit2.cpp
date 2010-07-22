#include "KTextEdit2.h"
#include <QTextCursor>
#include <QDebug>
#include <QMouseEvent>
#include <QApplication>
#include <QRegExp>
#include <KIcon>

KTextEdit2::KTextEdit2(QWidget* parent) : 
  KTextEdit(parent), 
  m_buffer(QApplication::clipboard()), 
  m_cirularBuffer(new ushort[8]), 
  m_circularBufferStart(0), 
  m_circularBufferEnd(-1),
  m_init(false),
  m_patternValueCounter(0)
  
{
  
}

uint KTextEdit2::registerWatchListItem(const QString item) 
{
  WatchString* aWatchString = new WatchString;
  aWatchString->length = item.size();
  aWatchString->string = new ushort[aWatchString->length];
  for (int i=0;i < aWatchString->length;i++) {
    aWatchString->string[i] = item[i].unicode();
  }
  m_watchList << aWatchString;
  m_patternValue[aWatchString] = ++m_patternValueCounter;
  return m_patternValueCounter;
}

void KTextEdit2::mouseReleaseEvent(QMouseEvent* event) 
{
  QTextCursor cur = textCursor();
  qDebug() << "mouse: " << event->button();
  
  if ((event->button() == Qt::MidButton) || (event->button() == Qt::LeftButton)) {
    cur.select(QTextCursor::WordUnderCursor);
    QString word = cur.selectedText();
    if (event->button() == Qt::MidButton) {
      //cur.movePosition(QTextCursor::StartOfWord);
      //int positionStart = tc.position();
      //cur.movePosition(QTextCursor::EndOfWord);
      qDebug() << "Button" << word;
      emit actionTriggered(word,m_buffer->text(QClipboard::Selection));
    }
    else if (event->button() == Qt::LeftButton) {
      emit actionTriggered(word);
      qDebug() << "Button" ;
      KTextEdit::mouseReleaseEvent(event);
    }
  }
  else
    KTextEdit::mouseReleaseEvent(event);
}

void KTextEdit2::contextMenuEvent(QContextMenuEvent* event) 
{
  QTextCursor cur = textCursor();
  KMenu* aMenu = new KMenu(this);
  emit contextMenuRequested(cur.selectedText(),aMenu);
  aMenu->popup(event->pos());
  //KTextEdit::contextMenuEvent(event);
}

void KTextEdit2::keyReleaseEvent(QKeyEvent* event) 
{
  //Implement a circular buffer algoritm and compare the string (pure C for performance)
  if ((event->type() == QEvent::KeyRelease) && (m_watchList.size())) {
    m_circularBufferEnd = (m_circularBufferEnd==7)?0:m_circularBufferEnd+1;
    if ((m_circularBufferStart == m_circularBufferEnd) && m_init)
      m_circularBufferStart = (m_circularBufferStart==7)?0:m_circularBufferStart+1;
    m_cirularBuffer[m_circularBufferEnd] = ((QKeyEvent*) event)->text()[0].unicode(); //Convert the character typed by the user to a 16bit integer
    
    uchar length = (8-m_circularBufferStart)+m_circularBufferEnd +1;
    if (length>8)
      length = m_circularBufferEnd+1;
    
    qDebug("start: %d End: %d Length: %d m_cirularBuffer: ",m_circularBufferStart,m_circularBufferEnd,length); //Leave those connected line for testing purpose
    qDebug() << QChar(m_cirularBuffer[0]) << QChar(m_cirularBuffer[1]) << QChar(m_cirularBuffer[2]) << QChar(m_cirularBuffer[3]) << QChar(m_cirularBuffer[4]) << QChar(m_cirularBuffer[5]) << QChar(m_cirularBuffer[6]) << QChar(m_cirularBuffer[7]) << "\n";
    
    for (ushort j = 0; j < m_watchList.size();j++) {//TODO handle backspace
      if ((m_watchList[j]->string[m_watchList[j]->length-1] == m_cirularBuffer[m_circularBufferEnd]) && (length >= m_watchList[j]->length)) {
	bool match = true;
	for (int i =0; i < m_watchList[j]->length-1;i++) { //Loop the string from right to left
	  qDebug() << "Comparing: "<< QChar(m_watchList[j]->string[m_watchList[j]->length-i-2]) << " at position: " << (m_watchList[j]->length-i-2) << " with:" << QChar(m_cirularBuffer[(m_circularBufferEnd-i-1>=0)?m_circularBufferEnd-i-1:8+(m_circularBufferEnd-i-1)]) << " at position: " << ((m_circularBufferEnd-i-1>=0)?m_circularBufferEnd-i-1:8+(m_circularBufferEnd-i-1)); 
	  if (m_cirularBuffer[(m_circularBufferEnd-i-1>=0)?m_circularBufferEnd-i-1:8+(m_circularBufferEnd-i-1)] != m_watchList[j]->string[m_watchList[j]->length-i-2]) {
	    match = false;
	    break;
	  }
	}
	if (match) {
	  qDebug() << "\n\n--Patern found" << m_watchList[j]->string << "--\n\n";
	  emit patternTyped(m_patternValue[m_watchList[j]]);
	}
      }
      m_init = true;
    }
  }
  KTextEdit::keyReleaseEvent(event);
}