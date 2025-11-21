#include "mainwindow.h"

#include <QApplication>
//#include "formpointtable.h"
//#include "formcommunch.h"
//#include "formcommundev.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //// 关键：注册 元类型（必须在信号槽连接前执行）
    //qRegisterMetaType<FormPointTable *>("FormPointTable *");
    //qRegisterMetaType<FormCommunCh *>("FormCommunCh *");
    //qRegisterMetaType<FormCommunDev *>("FormCommunDev *");

    MainWindow w;
    w.show();
    return a.exec();
}
