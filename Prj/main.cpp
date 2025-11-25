#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
//#include "formpointtable.h"
//#include "formcommunch.h"
//#include "formcommundev.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 获取可执行文件所在的目录路径
    QString appPath = QCoreApplication::applicationDirPath();
    qDebug() << "应用程序可执行文件所在目录:" << appPath;

    // 你可以使用 QDir 来操作这个路径
    QDir appDir(appPath);
    qDebug() << "应用程序目录的绝对路径:" << appDir.absolutePath();

    // 例如，拼接一个配置文件路径
    QString configFilePath = appDir.filePath("config.ini");
    qDebug() << "配置文件路径:" << configFilePath;

    MainWindow w;
    w.show();
    return a.exec();
}
