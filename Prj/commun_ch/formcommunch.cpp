#include "formcommunch.h"
#include "ui_formcommunch.h"
#include "app.h"

FormCommunCh::FormCommunCh(App::ChType_E type, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormCommunCh)
    , type_(type)
{
    ui->setupUi(this);

    // 工程名设置为只读
    ui->lineEdit_PrjName->setReadOnly(true);
    // 禁用下拉框
    ui->comboBox_Type->setEnabled(false);
    // 添加下拉框选项
    ui->comboBox_Type->addItem(App::CommunChTypeDlt645);
    ui->comboBox_Type->addItem(App::CommunChTypeModbusRtu);
    ui->comboBox_Type->addItem(App::CommunChTypeModbusTcp);

    ui->comboBox_Type->setCurrentText(App::ChTypeId2Str(type_));
}

FormCommunCh::~FormCommunCh()
{
    delete ui;
}

// 设置工程名
void FormCommunCh::SetPrjName(const QString &name)
{
    ui->lineEdit_PrjName->setText(name);
}

// 下拉框槽函数
void FormCommunCh::on_comboBox_Type_currentTextChanged(const QString &arg1)
{
    if(arg1 == App::CommunChTypeDlt645) {
        ui->stackedWidget->setCurrentWidget(ui->page_Dlt645);
    }
    else if(arg1 == App::CommunChTypeModbusRtu) {
        ui->stackedWidget->setCurrentWidget(ui->page_MRtu);
    }
    else if(arg1 == App::CommunChTypeModbusTcp) {
        ui->stackedWidget->setCurrentWidget(ui->page_MTcp);
    }
}

