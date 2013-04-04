#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("windows-1251"));
    QApplication a(argc, argv);
    MyWidget w;
    w.resize(860,500);
    w.setMinimumSize(860,500);
    w.setWindowTitle("PC Helper ver. 1.0");
    w.show();
    return a.exec();
}
