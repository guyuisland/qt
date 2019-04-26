#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
//#include"imfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTextCodec *codec = QTextCodec::codecForName("utf8"); //GBK gbk
    w.show();

    return a.exec();
}
