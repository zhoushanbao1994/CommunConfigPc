#include "formcommundev.h"
#include "ui_formcommundev.h"
#include "app.h"

FormCommunDev::FormCommunDev(App::DevType_E type, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormCommunDev)
    , type_(type)
{
    ui->setupUi(this);

    // 工程名设置为只读
    ui->lineEdit_PrjName->setReadOnly(true);
    // 禁用下拉框
    ui->comboBox_Type->setEnabled(false);
    // 添加下拉框选项
    ui->comboBox_Type->addItem(App::CommunDevTypeDlt645);
    ui->comboBox_Type->addItem(App::CommunDevTypeModbusRtu);
    ui->comboBox_Type->addItem(App::CommunDevTypeModbusTcp);

    ui->comboBox_Type->setCurrentText(App::DevTypeId2Str(type_));
}

FormCommunDev::~FormCommunDev()
{
    delete ui;
}

// 设置工程名
void FormCommunDev::SetPrjName(const QString &name)
{
    ui->lineEdit_PrjName->setText(name);
}

// 下拉框槽函数
void FormCommunDev::on_comboBox_Type_currentTextChanged(const QString &arg1)
{
    if(arg1 == App::CommunDevTypeDlt645) {
        ui->stackedWidget->setCurrentWidget(ui->page_Dlt645);
    }
    else if(arg1 == App::CommunDevTypeModbusRtu) {
        ui->stackedWidget->setCurrentWidget(ui->page_MRtu);
    }
    else if(arg1 == App::CommunDevTypeModbusTcp) {
        ui->stackedWidget->setCurrentWidget(ui->page_MTcp);
    }
}

void FormCommunDev::RefreshCbOption(
    const QStringList &tab_list, const QStringList &ch_list)
{
    switch(type_) {
    case App::kDevType_ModbusRtu:
        RefreshMrtuCbOption(tab_list, ch_list);
        break;
    case App::kDevType_ModbusTcp:
        RefreshMtcpCbOption(tab_list, ch_list);
        break;
    case App::kDevType_Dlt645:
        RefreshDltCbOption(tab_list, ch_list);
        break;
    default:
        break;
    }
}
void FormCommunDev::RefreshMrtuCbOption(
    const QStringList &tab_list, const QStringList &ch_list)
{
    QString curr_point_tab = ui->comboBox_MrtuPointTab->currentText();
    ui->comboBox_MrtuPointTab->clear();
    ui->comboBox_MrtuPointTab->addItems(tab_list);
    if(ui->comboBox_MrtuPointTab->findText(curr_point_tab) >= 0) {
        ui->comboBox_MrtuPointTab->setCurrentText(curr_point_tab);
    }

    QString curr_ch = ui->comboBox_MrtuCh->currentText();
    ui->comboBox_MrtuCh->clear();
    ui->comboBox_MrtuCh->addItems(ch_list);
    if(ui->comboBox_MrtuCh->findText(curr_ch) >= 0) {
        ui->comboBox_MrtuCh->setCurrentText(curr_ch);
    }
}
void FormCommunDev::RefreshMtcpCbOption(
    const QStringList &tab_list, const QStringList &ch_list)
{
    QString curr_point_tab = ui->comboBox_MtcpPointTab->currentText();
    ui->comboBox_MtcpPointTab->clear();
    ui->comboBox_MtcpPointTab->addItems(tab_list);
    if(ui->comboBox_MtcpPointTab->findText(curr_point_tab) >= 0) {
        ui->comboBox_MtcpPointTab->setCurrentText(curr_point_tab);
    }

    QString curr_ch = ui->comboBox_MtcpCh->currentText();
    ui->comboBox_MtcpCh->clear();
    ui->comboBox_MtcpCh->addItems(ch_list);
    if(ui->comboBox_MtcpCh->findText(curr_ch) >= 0) {
        ui->comboBox_MtcpCh->setCurrentText(curr_ch);
    }
}
void FormCommunDev::RefreshDltCbOption(
    const QStringList &tab_list, const QStringList &ch_list)
{
    QString curr_point_tab = ui->comboBox_DltPointTab->currentText();
    ui->comboBox_DltPointTab->clear();
    ui->comboBox_DltPointTab->addItems(tab_list);
    if(ui->comboBox_DltPointTab->findText(curr_point_tab) >= 0) {
        ui->comboBox_DltPointTab->setCurrentText(curr_point_tab);
    }

    QString curr_ch = ui->comboBox_DltCh->currentText();
    ui->comboBox_DltCh->clear();
    ui->comboBox_DltCh->addItems(ch_list);
    if(ui->comboBox_DltCh->findText(curr_ch) >= 0) {
        ui->comboBox_DltCh->setCurrentText(curr_ch);
    }
}

