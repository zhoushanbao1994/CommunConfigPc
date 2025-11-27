#include "formcommundev.h"
#include "ui_formcommundev.h"
#include "app.h"
#include <QDebug>

FormCommunDev::FormCommunDev(
    App::DevType_E type, QTreeWidgetItem *item,  QString &prjName,
    QString &customName, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormCommunDev)
    , type_(type)
    , item_(item)
{
    ui->setupUi(this);

    // 1. 定义正则表达式：允许 A-Z、a-z、0-9、_，并且长度在 0 到 16 位之间
    QRegExp regExp("^[A-Za-z0-9_]{0,16}$");
    // 2. 创建验证器
    QRegExpValidator *validator = new QRegExpValidator(regExp, ui->lineEdit_PrjName);
    // 3. 设置验证器到 QLineEdit
    ui->lineEdit_PrjName->setValidator(validator);
    // 设置提示字符
    ui->lineEdit_PrjName->setPlaceholderText("请输入字母、数字或下划线（最多16位）...");
    // 设置工程名
    ui->lineEdit_PrjName->setText(prjName);
    // 工程名设置为只读
    //ui->lineEdit_PrjName->setReadOnly(true);
    // 设置自定义名称
    ui->lineEdit_CustomName->setText(customName);
    // 连接 textEdited 信号
    QObject::connect(ui->lineEdit_PrjName, &QLineEdit::textEdited,
                     this, &FormCommunDev::PrjNameTextEdited_Slot);
    QObject::connect(ui->lineEdit_CustomName, &QLineEdit::textEdited,
                     this, &FormCommunDev::CustomNameTextEdited_Slot);
    // 禁用下拉框
    ui->comboBox_Type->setEnabled(false);
    // 添加下拉框选项
    ui->comboBox_Type->addItem(App::kStrCommunDevTypeDlt645);
    ui->comboBox_Type->addItem(App::kStrCommunDevTypeModbusRtu);
    ui->comboBox_Type->addItem(App::kStrCommunDevTypeModbusTcp);

    ui->comboBox_Type->setCurrentText(App::DevTypeId2Str(type_));
}

FormCommunDev::~FormCommunDev()
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "析构函数";
    delete ui;
}

// 下拉框槽函数
void FormCommunDev::on_comboBox_Type_currentTextChanged(const QString &arg1)
{
    if(arg1 == App::kStrCommunDevTypeDlt645) {
        ui->stackedWidget->setCurrentWidget(ui->page_Dlt645);
    }
    else if(arg1 == App::kStrCommunDevTypeModbusRtu) {
        ui->stackedWidget->setCurrentWidget(ui->page_MRtu);
    }
    else if(arg1 == App::kStrCommunDevTypeModbusTcp) {
        ui->stackedWidget->setCurrentWidget(ui->page_MTcp);
    }
}

void FormCommunDev::PrjNameTextEdited_Slot(const QString &text)
{
    if(item_ == nullptr) {
        return;
    }
    QString custom_name = ui->lineEdit_CustomName->text();
    item_->setText(0, text + ":" + custom_name);
}

void FormCommunDev::CustomNameTextEdited_Slot(const QString &text)
{
    if(item_ == nullptr) {
        return;
    }
    QString prj_name = ui->lineEdit_PrjName->text();
    item_->setText(0, prj_name + ":" + text);
}

// 刷新下拉框选项
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
// 刷新ModbusRtu页面下拉框选项
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
// 刷新ModbusTcp页面下拉框选项
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
// 刷新Dlt645页面下拉框选项
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
// 设置页面参数
void FormCommunDev::SetPageParameter(
    const QString &pointPrjName, const QString &chPrjName, const QString &addr)
{
    bool ok;
    switch(type_) {
    case App::kDevType_ModbusRtu:
        SetModbusRtuPageParameter(pointPrjName, chPrjName, App::StringToNumber(addr, ok));
        break;
    case App::kDevType_ModbusTcp:
        SetModbusTcpPageParameter(pointPrjName, chPrjName, App::StringToNumber(addr, ok));
        break;
    case App::kDevType_Dlt645:
        SetDlt645PageParameter(pointPrjName, chPrjName, addr);
        break;
    default:
        break;
    }
}
// 设置ModbusRtu页面参数
void FormCommunDev::SetModbusRtuPageParameter(
    const QString &pointPrjName, const QString &chPrjName, quint8 addr)
{
    App::SetComboBoxCurrentText(ui->comboBox_MrtuPointTab, pointPrjName, ':');
    App::SetComboBoxCurrentText(ui->comboBox_MrtuCh, chPrjName, ':');
    ui->spinBox_MrtuDevAddr->setValue(addr);
}
// 设置ModbusTcp页面参数
void FormCommunDev::SetModbusTcpPageParameter(
    const QString &pointPrjName, const QString &chPrjName, quint8 addr)
{
    App::SetComboBoxCurrentText(ui->comboBox_MtcpPointTab, pointPrjName, ':');
    App::SetComboBoxCurrentText(ui->comboBox_MtcpCh, chPrjName, ':');
    ui->spinBox_MtcpDevAddr->setValue(addr);
}
// 设置DLT645页面参数
void FormCommunDev::SetDlt645PageParameter(
    const QString &pointPrjName, const QString &chPrjName, const QString &addr)
{
    App::SetComboBoxCurrentText(ui->comboBox_DltPointTab, pointPrjName, ':');
    App::SetComboBoxCurrentText(ui->comboBox_DltCh, chPrjName, ':');
    ui->lineEdit_DltDevAddr->setText(addr);
}

// 获取页头参数
void FormCommunDev::GetHeaderParameter(
    QString &prjName, QString &customName)
{
    prjName = ui->lineEdit_PrjName->text();
    customName = ui->lineEdit_CustomName->text();
}
// 获取页面参数
void FormCommunDev::GetPageParameter(
    QString &pointPrjName, QString &chPrjName, QString &addr)
{
    quint8 u8_addr = 1;
    switch(type_) {
    case App::kDevType_ModbusRtu:
        GetModbusRtuPageParameter(pointPrjName, chPrjName, u8_addr);
        addr = QString(u8_addr);
        break;
    case App::kDevType_ModbusTcp:
        GetModbusTcpPageParameter(pointPrjName, chPrjName, u8_addr);
        addr = QString(u8_addr);
        break;
    case App::kDevType_Dlt645:
        GetDlt645PageParameter(pointPrjName, chPrjName, addr);
        break;
    default:
        break;
    }
}
// 获取ModbusRtu页面参数
void FormCommunDev::GetModbusRtuPageParameter(
    QString &pointPrjName, QString &chPrjName, quint8 &addr)
{
    pointPrjName = App::GetComboBoxCurrentText(ui->comboBox_MrtuPointTab, ':');
    chPrjName = App::GetComboBoxCurrentText(ui->comboBox_MrtuCh, ':');
    addr = ui->spinBox_MrtuDevAddr->value();
}
// 获取ModbusTcp页面参数
void FormCommunDev::GetModbusTcpPageParameter(
    QString &pointPrjName, QString &chPrjName, quint8 &addr)
{
    pointPrjName = App::GetComboBoxCurrentText(ui->comboBox_MtcpPointTab, ':');
    chPrjName = App::GetComboBoxCurrentText(ui->comboBox_MtcpCh, ':');
    addr = ui->spinBox_MtcpDevAddr->value();
}
// 获取DLT645页面参数
void FormCommunDev::GetDlt645PageParameter(
    QString &pointPrjName, QString &chPrjName, QString &addr)
{
    pointPrjName = App::GetComboBoxCurrentText(ui->comboBox_DltPointTab, ':');
    chPrjName = App::GetComboBoxCurrentText(ui->comboBox_DltCh, ':');
    addr = ui->lineEdit_DltDevAddr->text();
}
