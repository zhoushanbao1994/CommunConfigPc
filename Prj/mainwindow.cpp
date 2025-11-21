#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 工程栏添加、选中、删除操作后，发送信号告诉主窗口是否进行添加显示、显示、删除等操作
    QObject::connect(ui->widget_PrjSection, &ProjectSection::Form_Signal,
                     this, &MainWindow::Form_Slot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// action:1新增;0显示,-1删除;
void MainWindow::Form_Slot(QWidget *form, int action)
{
    qDebug() << __FUNCTION__ << __LINE__ << action;
    // 新增
    if(action == 1) {
        ui->stackedWidget->addWidget(form);
        ui->stackedWidget->setCurrentWidget(form);
    }
    // 显示
    else if(action == 0) {
        ui->stackedWidget->setCurrentWidget(form);
    }
    // 删除
    else if(action == -1) {
        ui->stackedWidget->setCurrentWidget(ui->page);
        ui->stackedWidget->removeWidget(form);
    }
}
