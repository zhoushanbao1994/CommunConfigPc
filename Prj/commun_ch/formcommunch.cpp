#include "formcommunch.h"
#include "ui_formcommunch.h"
#include "app.h"
#include <QDebug>

FormCommunCh::FormCommunCh(
    App::ChType_E type, QTreeWidgetItem *item, QString &prj_name, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormCommunCh)
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
    ui->lineEdit_PrjName->setText(prj_name);
    // 工程名设置为只读
    //ui->lineEdit_PrjName->setReadOnly(true);
    // 连接 textEdited 信号
    QObject::connect(ui->lineEdit_PrjName, &QLineEdit::textEdited,
                     this, &FormCommunCh::PrjNameTextEdited_Slot);
    QObject::connect(ui->lineEdit_CustomName, &QLineEdit::textEdited,
                     this, &FormCommunCh::CustomNameTextEdited_Slot);
    // 禁用下拉框
    ui->comboBox_Type->setEnabled(false);
    // 添加下拉框选项
    ui->comboBox_Type->addItem(App::kStrCommunChTypeDlt645);
    ui->comboBox_Type->addItem(App::kStrCommunChTypeModbusRtu);
    ui->comboBox_Type->addItem(App::kStrCommunChTypeModbusTcp);

    ui->comboBox_Type->setCurrentText(App::ChTypeId2Str(type_));
}

FormCommunCh::~FormCommunCh()
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "析构函数";
    delete ui;
}

// 下拉框槽函数
void FormCommunCh::on_comboBox_Type_currentTextChanged(const QString &arg1)
{
    if(arg1 == App::kStrCommunChTypeDlt645) {
        ui->stackedWidget->setCurrentWidget(ui->page_Dlt645);
    }
    else if(arg1 == App::kStrCommunChTypeModbusRtu) {
        ui->stackedWidget->setCurrentWidget(ui->page_MRtu);
    }
    else if(arg1 == App::kStrCommunChTypeModbusTcp) {
        ui->stackedWidget->setCurrentWidget(ui->page_MTcp);
    }
}

void FormCommunCh::PrjNameTextEdited_Slot(const QString &text)
{
    if(item_ == nullptr) {
        return;
    }
    QString custom_name = ui->lineEdit_CustomName->text();
    item_->setText(0, text + ":" + custom_name);
}

void FormCommunCh::CustomNameTextEdited_Slot(const QString &text)
{
    if(item_ == nullptr) {
        return;
    }
    QString prj_name = ui->lineEdit_PrjName->text();
    item_->setText(0, prj_name + ":" + text);
}

// 设置ModbusRtu页面参数
void FormCommunCh::SetModbusRtuPageParameter(
    const QString &interface, const QString &baudRate,
    const QString &dataBits, const QString &parity, const QString &stopBits)
{
    ui->comboBox_MrtuInterface->setCurrentText(interface);
    ui->comboBox_MrtuBaudRate->setCurrentText(baudRate);
    ui->comboBox_MrtuDataBits->setCurrentText(dataBits);
    ui->comboBox_MrtuCheckBits->setCurrentText(App::ParityFormatting(parity));
    ui->comboBox_MrtuStopBits->setCurrentText(stopBits);
}
// 设置ModbusTcp页面参数
void FormCommunCh::SetModbusTcpPageParameter(
    const QString &ip, quint16 port)
{
    ui->lineEdit_MtcpIpAddr->setText(ip);
    ui->spinBox_MtcpPort->setValue(port);
}
// 设置DLT645页面参数
void FormCommunCh::SetDlt645PageParameter(
    const QString &interface, const QString &baudRate,
    const QString &dataBits, const QString &parity, const QString &stopBits)
{
    ui->comboBox_DltInterface->setCurrentText(interface);
    ui->comboBox_DltBaudRate->setCurrentText(baudRate);
    ui->comboBox_DltDataBits->setCurrentText(dataBits);
    ui->comboBox_DltCheckBits->setCurrentText(App::ParityFormatting(parity));
    ui->comboBox_DltStopBits->setCurrentText(stopBits);
}
