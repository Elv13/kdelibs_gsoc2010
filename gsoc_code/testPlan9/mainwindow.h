#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <KXmlGuiWindow>
#include <QSyntaxHighlighter>
#include <QHash>
#include "KToolBar2.h"
#include "KPushButton2.h"
#include "KActionArg.h"
#include "lib/KTextEdit2.h"
 
class MainWindow : public KMainWindow
{
  Q_OBJECT
  public:
    MainWindow(QWidget *parent=0, QString windowTitle = "New Document");
    KTextEdit2* m_textArea;
    
  private:
    KToolBar2* m_testToolBar;
    void setupActions();
    QHash<QString,KArgAction*> m_actionCollection;
  private slots:
    void find(QString text);
    void open(QString path);
    void newDoc(QString text);
    void matchAction(QString name, QString arg = "");
};

class SyntaxHighlighter : public QSyntaxHighlighter {
public:
  SyntaxHighlighter(QTextEdit* parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;
    singleLineCommentFormat.setForeground(Qt::gray);
    singleLineCommentFormat.setBackground(Qt::blue);
    //singleLineCommentFormat.setFontBold(true);
    rule.pattern = QRegExp("#KText::UI[a-zA-Z0-9,.\\;\\:\\-_\\ ]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

  }
  
  void highlightBlock(const QString &text) {
    foreach (HighlightingRule rule, highlightingRules) {
      QRegExp expression(rule.pattern);
      int index = text.indexOf(expression);
      while (index >= 0) {
          int length = expression.matchedLength();
          setFormat(index, length, rule.format);
          index = text.indexOf(expression, index + length);
      }
    }

    setCurrentBlockState(0);
  }


private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;
    QTextCharFormat singleLineCommentFormat;
};
 
#endif