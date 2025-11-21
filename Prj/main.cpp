#include "mainwindow.h"

#include <QApplication>
//#include "formpointtable.h"
//#include "formcommunch.h"
//#include "formcommundev.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
