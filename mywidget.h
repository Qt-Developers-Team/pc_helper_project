#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtWebKit>


class MyWidget : public QWidget
{
    Q_OBJECT

protected:
//    virtual void mouseDoubleClickEvent(QMouseEvent *pe)
//    {
//       if (pe->FocusOut())
//       // QMessageBox::information(0, "Warning", "Work!");
//        this->close();
//    }
    bool event(QEvent *e)
    {
       if (e->type() == QEvent::WindowDeactivate)
        //QMessageBox::information(0, "Warning", "Work!");
        this->close();
       else QWidget::event(e);
       return 0;
    }

public:
    QFileSystemModel *model;

    QWidget *pCenterWidget;

    QPushButton *pButtonBackward;
    QPushButton *pButtonForward;
    QPushButton *pButtonBookmarks;
    QPushButton *pButtonFeedback;
    QPushButton *pButtonNext;
    QPushButton *pButtonPrevious;

    QLineEdit *pLineEdit;

    QSplitter *pSplitter;
    QTabWidget *pTabWidget;


    //QTreeWidget *pArticleTree;
    QTreeView   *pArticleTreeView;
    //QTreeView   *pAdviceTreeView;

    QTableView  *pTableView;

    //QLabel *pMainLabel;
    QLabel *pInfoLabel;

    QWebView *pHTMLFile;
public:
    MyWidget(QWidget *parent = 0);
private slots:
    //void openLink(QUrl);
    //void openTreeLink(QTreeWidgetItem*);
    void getHTML(QModelIndex);
};

#endif // MYWIDGET_H
