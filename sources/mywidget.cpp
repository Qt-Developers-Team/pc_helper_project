#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    // create widgets

    model = new QDirModel;

    pCenterWidget = new QWidget;
    pTableView = new QTableView;

    pButtonBackward = new QPushButton("<= &Backward");
    pButtonForward = new QPushButton("&Forward =>");
    pButtonBookmarks = new QPushButton("&Add Bookmark");
    pButtonFeedback = new QPushButton("&Leave feedback :)");
    pButtonNext = new QPushButton("&Next");
    pButtonPrevious = new QPushButton("&Previous");

    pLineEdit = new QLineEdit;

    pSplitter = new QSplitter(Qt::Horizontal);

    pTabWidget = new QTabWidget;

    pArticleTreeView = new QTreeView;
    pAdviceTreeView = new QTreeView;

    //test HTML
    QWebView *pHTMLFile = new QWebView;
    //QString path=QApplication::applicationDirPath()+"/test4.html";
    //QUrl *debugURL = new QUrl(QUrl::fromLocalFile(QString("test4.html")));
    //pHTMLFile->load(QUrl(path));
    pHTMLFile->load(QUrl("test3.htm"));
    //pHTMLFile->load(QUrl("http://google.ru"));
    //pHTMLFile->resize(200, 200);
//    QFile *pHTMLFile = new QFile("test.html");
//    QTextStream read_in(pHTMLFile);
//    QString HTMLdata = read_in.readAll();
  //  pMainLabel = new QLabel("Some useful information");
 //   pMainLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
//     }


    pInfoLabel = new QLabel("PC-Helper v. 1.0 by Ayrat, RoK & (Diego) ");

    // setup model

    pArticleTreeView->setModel(model);
    pAdviceTreeView->setModel(model);
    pTableView->setModel(model);
    
    // connection setup

    connect(pArticleTreeView, SIGNAL(clicked(const QModelIndex&)),
            pTableView, SLOT(setRootIndex(const QModelIndex&))
            );

    connect(pTableView, SIGNAL(activated(const QModelIndex&)),
            pArticleTreeView, SLOT(setCurrentIndex(const QModelIndex&))
            );

    connect(pTableView, SIGNAL(activated(const QModelIndex&)),
            pTableView, SLOT(setRootIndex(const QModelIndex&))
            );


    pTabWidget->addTab(pArticleTreeView, "Articles");
    pTabWidget->addTab(pAdviceTreeView, "Advices");
    //pTabWidget->resize(200, 400);
    pTabWidget->setMinimumWidth(200);


    // Layout setup

    QVBoxLayout *ExteriorLayout = new QVBoxLayout;
    QHBoxLayout *NavigationLayout = new QHBoxLayout;
    QHBoxLayout *InfoLayout = new QHBoxLayout;
    QVBoxLayout *MainLayout = new QVBoxLayout;
    QHBoxLayout *MainButtonsLayout = new QHBoxLayout;

    MainButtonsLayout->addWidget(pButtonPrevious);
    MainButtonsLayout->addStretch(1);
    MainButtonsLayout->addWidget(pButtonNext);

    //MainLayout->addWidget(pTableView); // temporary
    //MainLayout->addWidget(pMainLabel);
    MainLayout->addWidget(pHTMLFile);
    MainLayout->addLayout(MainButtonsLayout);

    pCenterWidget->setLayout(MainLayout);
    pSplitter->addWidget(pTabWidget);
    pSplitter->addWidget(pCenterWidget);
    pSplitter->setChildrenCollapsible(false);
    QPoint tmp = pSplitter->pos();
    pSplitter->width();

    ExteriorLayout->setMargin(10);
    ExteriorLayout->setSpacing(10);
    ExteriorLayout->addLayout(NavigationLayout);
    ExteriorLayout->addWidget(pSplitter, 15);
    ExteriorLayout->addLayout(InfoLayout);

    NavigationLayout->addWidget(pButtonBackward);
    NavigationLayout->addWidget(pButtonForward);
    NavigationLayout->addWidget(pLineEdit);
    NavigationLayout->addWidget(pButtonBookmarks);

    InfoLayout->addWidget(pButtonFeedback);
    InfoLayout->addStretch(1);
    InfoLayout->addWidget(pInfoLabel);

    setLayout(ExteriorLayout);

}



//void MyWidget::focusOutEvent(QFocusEvent *pe)
//{
//
//}
