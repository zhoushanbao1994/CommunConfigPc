#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "formpointtable.h"
//#include "formcommunch.h"
//#include "formcommundev.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Form_Slot(QWidget *form, int action); // action:1新增;0显示,-1删除;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
