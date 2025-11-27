#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jsonparse.h"
#include "jsongenerat.h"
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
    JsonParse *jsonParse = new JsonParse();
    QMap<QString, ModbusPointStruct::PointTab_T> mpts = jsonParse->GetModbusPointTabs();// Modbus点表
    QMap<QString, Dlt645PointStruct::PointTab_T> dpts = jsonParse->GetDlt645PointTabs();// DLT645点表
    //QString mrcfn = jsonParse->GetModbusRtuChFileName();                                // ModbusRtu通道的文件名
    //QString mtcfn = jsonParse->GetModbusTcpChFileName();                                // ModbusTcp通道的文件名
    //QString dlcfn = jsonParse->GetDlt645ChFileName();                                   // DLT645通道的文件名
    QMap<QString, ModbusRtuChStruct::Ch_T> mrcs = jsonParse->GetModbusRtuChs();         // ModbusRtu通道
    QMap<QString, ModbusTcpChStruct::Ch_T> mtcs = jsonParse->GetModbusTcpChs();         // ModbusTcp通道
    QMap<QString, Dlt645ChStruct::Ch_T> dlcs = jsonParse->GetDlt645Chs();               // DLT645通道
    //QString mrdfn = jsonParse->GetModbusRtuDevFileName();                               // ModbusRtu设备的文件名
    //QString mtdfn = jsonParse->GetModbusTcpDevFileName();                               // ModbusTcp设备的文件名
    //QString dldfn = jsonParse->GetDlt645DevFileName();                                  // DLT645设备的文件名
    QMap<QString, ModbusRtuDevStruct::Dev_T> mrds = jsonParse->GetModbusRtuDevs();      // ModbusRtu设备
    QMap<QString, ModbusTcpDevStruct::Dev_T> mtds = jsonParse->GetModbusTcpDevs();      // ModbusTcp设备
    QMap<QString, Dlt645DevStruct::Dev_T> dlds = jsonParse->GetDlt645Devs();            // DLT645设备
    delete jsonParse;
    jsonParse = nullptr;

    ui->widget_PrjSection->SetModbusPointTabs(mpts);    // Modbus点表
    ui->widget_PrjSection->SetDlt645PointTabs(dpts);    // DLT645点表
    ui->widget_PrjSection->SetModbusRtuChs(mrcs);       // ModbusRtu通道
    ui->widget_PrjSection->SetModbusTcpChs(mtcs);       // ModbusTcp通道
    ui->widget_PrjSection->SetDlt645Chs(dlcs);          // DLT645通道
    ui->widget_PrjSection->SetModbusRtuDevs(mrds);      // ModbusRtu设备
    ui->widget_PrjSection->SetModbusTcpDevs(mtds);      // ModbusTcp设备
    ui->widget_PrjSection->SetDlt645Devs(dlds);         // DLT645设备
}

// 导出-槽函数
void MainWindow::on_actionExport_triggered()
{
    qDebug() << __FUNCTION__ << __LINE__;
    QString path = App::SelectExistFolder(
        this, App::settings, App::kExportFolderName, true);
    if (path.isEmpty()) {
        qDebug() << __FUNCTION__ << __LINE__ << "用户取消选择";
        return;
    }
    qDebug() << __FUNCTION__ << __LINE__ << "用户选择路径:" << path;

    QMap<QString, ModbusPointStruct::PointTab_T> mpts;  // 获取Modbus点表
    QMap<QString, Dlt645PointStruct::PointTab_T> dpts;  // 获取DLT645点表
    QMap<QString, ModbusRtuChStruct::Ch_T> mrcs;        // 获取ModbusRtu通道
    QMap<QString, ModbusTcpChStruct::Ch_T> mtcs;        // 获取ModbusTcp通道
    QMap<QString, Dlt645ChStruct::Ch_T> dlcs;           // 获取DLT645通道
    QMap<QString, ModbusRtuDevStruct::Dev_T> mrds;      // 获取ModbusRtu设备
    QMap<QString, ModbusTcpDevStruct::Dev_T> mtds;      // 获取ModbusTcp设备
    QMap<QString, Dlt645DevStruct::Dev_T> dlds;         // 获取DLT645设备

    bool debug = true;
    ui->widget_PrjSection->GetModbusPointTabs(mpts, debug); // 获取Modbus点表
    ui->widget_PrjSection->GetDlt645PointTabs(dpts, debug); // 获取DLT645点表
    ui->widget_PrjSection->GetModbusRtuChs(mrcs, debug);    // 获取ModbusRtu通道
    ui->widget_PrjSection->GetModbusTcpChs(mtcs, debug);    // 获取ModbusTcp通道
    ui->widget_PrjSection->GetDlt645Chs(dlcs, debug);       // 获取DLT645通道
    ui->widget_PrjSection->GetModbusRtuDevs(mrds, debug);   // 获取ModbusRtu设备
    ui->widget_PrjSection->GetModbusTcpDevs(mtds, debug);   // 获取ModbusTcp设备
    ui->widget_PrjSection->GetDlt645Devs(dlds, debug);      // 获取DLT645设备

    JsonGenerate *json_generate = new JsonGenerate(
        path, mpts, dpts, mrcs, mtcs, dlcs, mrds, mtds, dlds, debug);

    delete json_generate;
    json_generate = nullptr;
}

