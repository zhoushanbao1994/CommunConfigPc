#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jsonparse.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

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
    QString tmp = QString("%1:").arg(action);
    if(action == 1) { tmp += "新增"; } // 新增
    else if(action == 0) { tmp +="显示"; } // 显示
    else if(action == -1) { tmp += "删除"; } // 删除
    qDebug() << __FUNCTION__ << __LINE__ << "槽函数开始：" << tmp
             << ", 目标删除:" << form
             << ", 当前显示:" << ui->stackedWidget->currentWidget();
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
    qDebug() << __FUNCTION__ << __LINE__ << "槽函数结束：" << tmp
             << ", 目标删除:" << form
             << ", 当前显示:" << ui->stackedWidget->currentWidget();
}

// 新建-槽函数
void MainWindow::on_actionNew_triggered()
{
    qDebug() <<  __FUNCTION__ << __LINE__;

    ui->stackedWidget->setCurrentWidget(ui->page);
    ui->widget_PrjSection->ClearAll();
}

// 导入-槽函数
void MainWindow::on_actionImport_triggered()
{
    qDebug() <<  __FUNCTION__ << __LINE__;

    // 解析 JSON 数据
    JsonParse *json_parse = new JsonParse();

}

// 导出-槽函数
void MainWindow::on_actionExport_triggered()
{
    qDebug() <<  __FUNCTION__ << __LINE__;
}

