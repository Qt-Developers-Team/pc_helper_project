#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    // create widgets
    model = new QFileSystemModel;

    model->setRootPath(QDir::currentPath());

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

    //pArticleTree = new QTreeWidget;
    pArticleTreeView = new QTreeView;
    //pAdviceTreeView = new QTreeView;

    //test HTML
    pHTMLFile = new QWebView;
//    pHTMLFile->load(QUrl("PC.html"));
//    pHTMLFile->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
//    connect(pHTMLFile, SIGNAL(linkClicked(QUrl)), this, SLOT(openLink(QUrl)));


    pInfoLabel = new QLabel("PC-Helper v. 1.0 by Ayrat, RoK & Diego ");


    // tree filling

  /*  pArticleTree->setSortingEnabled(false);
    pArticleTree->setHeaderItem(NULL);
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(pArticleTree);
    treeItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    treeItem->setText(0, "Виды компьютеров");
    QTreeWidgetItem *treeItemDir = 0;
    for (int i = 1; i<4; ++i){
        treeItemDir = new QTreeWidgetItem(treeItem);
        switch (i)
        {
        case 1: 
            treeItemDir->setText(0, "PC"); break;
        case 2: 
            treeItemDir->setText(0, "Моноблок"); break;
        case 3:
            treeItemDir->setText(0, "Ноутбук"); break;
        }
    
    }
    treeItem = new QTreeWidgetItem(pArticleTree);
    treeItem->setText(0, "Устройство компьютера");
//    for (int i = 1; i<8; ++i){
        treeItemDir = new QTreeWidgetItem(treeItem);
        treeItemDir->setText(0, "Материнская плата");
//    }
    pArticleTree->setItemExpanded(treeItem, false);*/
    // setup model

    pArticleTreeView->setModel(model);
    pArticleTreeView->setRootIndex(model->index(QDir::currentPath()+ "/data/articles"));
   // pAdviceTreeView->setModel(model);
   // pTableView->setModel(model);
    
    // connection setup
     //connect(this->pArticleTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
     //        this, SLOT(openTreeLink(QTreeWidgetItem*)));


    connect(this->pArticleTreeView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(getHTML(QModelIndex))
            );
//
//    connect(pTableView, SIGNAL(activated(const QModelIndex&)),
//            pArticleTreeView, SLOT(setCurrentIndex(const QModelIndex&))
//            );
//
//    connect(pTableView, SIGNAL(activated(const QModelIndex&)),
//            pTableView, SLOT(setRootIndex(const QModelIndex&))
//            );



    // Layout setup

    QVBoxLayout *ExteriorLayout = new QVBoxLayout;
    QHBoxLayout *NavigationLayout = new QHBoxLayout;
    QHBoxLayout *InfoLayout = new QHBoxLayout;
    QVBoxLayout *MainLayout = new QVBoxLayout;
    QHBoxLayout *MainButtonsLayout = new QHBoxLayout;

    pTabWidget->addTab(pArticleTreeView, "Articles");
    //pTabWidget->addTab(pArticleTree, "Advices");
    //pTabWidget->addTab(pAdviceTree, "Advices");
    pTabWidget->setMinimumWidth(200);


    MainButtonsLayout->addWidget(pButtonPrevious);
    MainButtonsLayout->addStretch(1);
    MainButtonsLayout->addWidget(pButtonNext);


    MainLayout->addWidget(pHTMLFile);
    MainLayout->addLayout(MainButtonsLayout);

    pCenterWidget->setLayout(MainLayout);
    pSplitter->addWidget(pTabWidget);
    pSplitter->addWidget(pCenterWidget);
    pSplitter->setChildrenCollapsible(false);


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

//void MyWidget::openLink(QUrl link){
//    pHTMLFile->load(link);
//}
//void MyWidget::openTreeLink(QTreeWidgetItem *twi){
//    QString name = twi->text(0)+".html";
//    QFile *file = new QFile(name);
//    if (file->exists()){
//        pHTMLFile->load(QUrl(name));
//    }
//}

void MyWidget::getHTML(QModelIndex mi){
    bool isDir = model->isDir(mi);
    if (!isDir){
        QString *HTMLName = new QString(model->filePath(mi));
        //pInfoLabel->setText(model->data(mi, Qt::DisplayRole).toString());
        //pInfoLabel->setText(model->filePath(mi));
        QFile *file = new QFile(*HTMLName);
        if (file->exists()){
            pHTMLFile->load(QUrl(*HTMLName));
        }
    }
}
