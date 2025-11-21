#include "formpointtable.h"
#include "ui_formpointtable.h"
#include "app.h"
#include "hexdecvalidatordelegate.h"
#include "qwidgetcombox.h"
//#include "qwidgetcheckbox.h"

FormPointTable::FormPointTable(App::PointTabType_E type, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormPointTable)
    , type_(type)
{
    ui->setupUi(this);

    // 工程名设置为只读
    ui->lineEdit_PrjName->setReadOnly(true);
    // 禁用下拉框
    ui->comboBox_Type->setEnabled(false);
    // 添加下拉框选项
    ui->comboBox_Type->addItem(App::PointTableTypeDlt645);
    ui->comboBox_Type->addItem(App::PointTableTypeModbus);

    ui->comboBox_Type->setCurrentText(App::PointTabTypeId2Str(type_));

    QStringList str1, str2;
    str1 << "起始地址" << "点数量" << "功能码" << "数据类型" << "读取周期ms" << "名称";
    modbus_tab_ = new CustomTableWidget(str1, 1);
    ModbusTableWidget_RowSet(0, 0x0000, 10, kModbusFunCode_03H, kModbusDateType_U16, 1000, "数据段1");
    QObject::connect(modbus_tab_, &CustomTableWidget::InsertLine_Signal,
                     [&](int row_num){
                         ModbusTableWidget_RowSet(row_num, 0x0000, 10, kModbusFunCode_03H, kModbusDateType_U16, 1000, "");
                     });
    str2 << "数据标识" << "读取周期ms" << "名称";
    dlt645_tab_ = new CustomTableWidget(str2, 1);
    dlt645_tab_->horizontalHeader()->resizeSection(0, 300);
    Dlt645TableWidget_RowSet(
        0, kDltDataId07_00010000, 50000, kDltDataId07_00010000);
    QObject::connect(dlt645_tab_, &CustomTableWidget::InsertLine_Signal,
                     [&](int row_num){
                         Dlt645TableWidget_RowSet(row_num, kDltDataId07_00010000, 1000, "");
                     });

    ui->stackedWidget->addWidget(dlt645_tab_);
    ui->stackedWidget->addWidget(modbus_tab_);

    // 给第一列设置自定义委托（限制输入）
    QString sreg_m0 = "^0x[0-9a-fA-F]{1,4}$|^(?:6553[0-5]|655[0-2]\\d|65[0-4]\\d{2}|6[0-4]\\d{3}|[1-5]\\d{4}|\\d{1,4})$";
    HexDecValidatorDelegate *delegate_m0 = new HexDecValidatorDelegate(sreg_m0);
    modbus_tab_->setItemDelegateForColumn(0, delegate_m0); // 仅一列生效
    QString sreg_m1 = "^0x(?:0*[1-9a-fA-F]|0*[1-9a-fA-F][0-9a-fA-F]{1,3}|0*10000)$|^(?:6553[0-6]|655[0-2]\\d|65[0-4]\\d{2}|6[0-4]\\d{3}|[1-5]\\d{4}|[1-9]\\d{0,3})$";
    HexDecValidatorDelegate *delegate_m1 = new HexDecValidatorDelegate(sreg_m1);
    modbus_tab_->setItemDelegateForColumn(1, delegate_m1); // 仅一列生效
    QString sreg_m4 = "^(?:6553[0-5]|655[0-2]\\d|65[0-4]\\d{2}|6[0-4]\\d{3}|[1-5]\\d{4}|\\d{1,4})$";
    HexDecValidatorDelegate *delegate_m4 = new HexDecValidatorDelegate(sreg_m4, 4, HexDecValidatorDelegate::kResultFormat_Dec);
    modbus_tab_->setItemDelegateForColumn(4, delegate_m4); // 仅一列生效

    // 给第一列设置自定义委托（限制输入）
    QString sreg_d0 = "^0x[0-9a-fA-F]{1,8}$";
    HexDecValidatorDelegate *delegate_d0 = new HexDecValidatorDelegate(sreg_d0, 8);
    dlt645_tab_->setItemDelegateForColumn(0, delegate_d0); // 仅一列生效
    QString sreg_d1 = "^(?:6553[0-5]|655[0-2]\\d|65[0-4]\\d{2}|6[0-4]\\d{3}|[1-5]\\d{4}|\\d{1,4})$";
    HexDecValidatorDelegate *delegate_d1 = new HexDecValidatorDelegate(sreg_d1, 4, HexDecValidatorDelegate::kResultFormat_Dec);
    modbus_tab_->setItemDelegateForColumn(4, delegate_d1); // 仅一列生效
}

FormPointTable::~FormPointTable()
{
    delete ui;
}

// 设置工程名
void FormPointTable::SetPrjName(const QString &name)
{
    ui->lineEdit_PrjName->setText(name);
}

// 下拉框槽函数
void FormPointTable::on_comboBox_Type_currentTextChanged(const QString &arg1)
{
    if(arg1 == App::PointTableTypeDlt645) {
        //ui->stackedWidget->setCurrentWidget(ui->page_Dlt645);
        ui->stackedWidget->setCurrentWidget(dlt645_tab_);
    }
    else if(arg1 == App::PointTableTypeModbus) {
        //ui->stackedWidget->setCurrentWidget(ui->page_Modbus);
        ui->stackedWidget->setCurrentWidget(modbus_tab_);
    }
}

// 填充一行数据
void FormPointTable::ModbusTableWidget_RowSet(
    int row, quint16 start_addr, quint16 point_num, const QString &code,
    const QString &data_type, int read_cycle, const QString &name)
{
    // ************ 填充列：起始地址 ************
    QTableWidgetItem *item_start_addr = new QTableWidgetItem(
        QString("0x") + QString("%1").arg(start_addr, 4, 16, QChar('0')).toUpper() );
    modbus_tab_->setItem(row, kModbusTabColumnId_StartAddr, item_start_addr);
    // ************ 填充列：点数量 ************
    QTableWidgetItem *item_point_num = new QTableWidgetItem(
        QString("%1").arg(point_num) );
    modbus_tab_->setItem(row, kModbusTabColumnId_PointNum, item_point_num);
    // ************ 填充列：功能码 ************
    QStringList text_code;
    text_code.append(kModbusFunCode_01H);
    text_code.append(kModbusFunCode_02H);
    text_code.append(kModbusFunCode_03H);
    text_code.append(kModbusFunCode_04H);
    QWidgetComBox *item_func_code = new QWidgetComBox(text_code);
    item_func_code->setCurrentText(code);
    modbus_tab_->setCellWidget(row, kModbusTabColumnId_Code, item_func_code);
    // ************ 填充列：数据类型 ************
    QStringList text_type;
    text_type.append(kModbusDateType_U16);
    text_type.append(kModbusDateType_S16);
    text_type.append(kModbusDateType_U32);
    text_type.append(kModbusDateType_S32);
    QWidgetComBox *item_date_type = new QWidgetComBox(text_type);
    item_date_type->setCurrentText(data_type);
    modbus_tab_->setCellWidget(row, kModbusTabColumnId_DataType, item_date_type);
    // ************ 填充列：读取周期 ************
    QTableWidgetItem *item_read_cycle = new QTableWidgetItem(
        QString("%1").arg(read_cycle) );
    modbus_tab_->setItem(row, kModbusTabColumnId_ReadCycle, item_read_cycle);
    // ************ 填充列：名称 ************
    QTableWidgetItem *item_name = new QTableWidgetItem(
        QString("%1").arg(name) );
    modbus_tab_->setItem(row, kModbusTabColumnId_Name, item_name);
    //// ************ 填充复选框:"使能" ************
    //QWidgetCheckBox *enable = new QWidgetCheckBox ();    // 创建CheckBox
    //enable->setCheckState(enable == "true"?Qt::Checked:Qt::Unchecked);
    //modbus_tab_->setCellWidget(row, kTabColumnId_enable,
    //                               enable
    //                               ); //将widget放到table中

}

// 填充一行数据
void FormPointTable::Dlt645TableWidget_RowSet(
    int row, const QString &code, int read_cycle, const QString &name)
{
    // ************ 填充列：功能码 ************
    QStringList text_code;
    // DLT645 07数据标识
    text_code.append(kDltDataId07_00000000);    // "0x00000000_(当前)组合有功总电能";
    text_code.append(kDltDataId07_00000100);    // "0x00000100_(当前)组合有功费率 1 电能";
    text_code.append(kDltDataId07_00000200);    // "0x00000200_(当前)组合有功费率 2 电能";
    text_code.append(kDltDataId07_00000300);    // "0x00000300_(当前)组合有功费率 3 电能";
    text_code.append(kDltDataId07_00000400);    // "0x00000400_(当前)组合有功费率 4 电能";
    text_code.append(kDltDataId07_00000500);    // "0x00000500_(当前)组合有功费率 5 电能";
    text_code.append(kDltDataId07_00000600);    // "0x00000600_(当前)组合有功费率 6 电能";
    text_code.append(kDltDataId07_00000700);    // "0x00000700_(当前)组合有功费率 7 电能";
    text_code.append(kDltDataId07_00000800);    // "0x00000800_(当前)组合有功费率 8 电能";
    text_code.append(kDltDataId07_00010000);    // "0x00010000_(当前)正向有功总电能";
    text_code.append(kDltDataId07_00010100);    // "0x00010100_(当前)正向有功费率 1 电能";
    text_code.append(kDltDataId07_00010200);    // "0x00010200_(当前)正向有功费率 2 电能";
    text_code.append(kDltDataId07_00010300);    // "0x00010300_(当前)正向有功费率 3 电能";
    text_code.append(kDltDataId07_00010400);    // "0x00010400_(当前)正向有功费率 4 电能";
    text_code.append(kDltDataId07_00010500);    // "0x00010500_(当前)正向有功费率 5 电能";
    text_code.append(kDltDataId07_00010600);    // "0x00010600_(当前)正向有功费率 6 电能";
    text_code.append(kDltDataId07_00010700);    // "0x00010700_(当前)正向有功费率 7 电能";
    text_code.append(kDltDataId07_00010800);    // "0x00010800_(当前)正向有功费率 8 电能";
    text_code.append(kDltDataId07_00020000);    // "0x00020000_(当前)反向有功总电能";
    text_code.append(kDltDataId07_00020100);    // "0x00020100_(当前)反向有功费率 1 电能";
    text_code.append(kDltDataId07_00020200);    // "0x00020200_(当前)反向有功费率 2 电能";
    text_code.append(kDltDataId07_00020300);    // "0x00020300_(当前)反向有功费率 3 电能";
    text_code.append(kDltDataId07_00020400);    // "0x00020400_(当前)反向有功费率 4 电能";
    text_code.append(kDltDataId07_00020500);    // "0x00020500_(当前)反向有功费率 5 电能";
    text_code.append(kDltDataId07_00020600);    // "0x00020600_(当前)反向有功费率 6 电能";
    text_code.append(kDltDataId07_00020700);    // "0x00020700_(当前)反向有功费率 7 电能";
    text_code.append(kDltDataId07_00020800);    // "0x00020800_(当前)反向有功费率 8 电能";
    text_code.append(kDltDataId07_01010000);    // "0x01010000_(当前)正向有功总最大需量及发生时间";
    text_code.append(kDltDataId07_01010100);    // "0x01010100_(当前)正向有功费率 1 最大需量及发生时间";
    text_code.append(kDltDataId07_01010200);    // "0x01010200_(当前)正向有功费率 2 最大需量及发生时间";
    text_code.append(kDltDataId07_01010300);    // "0x01010300_(当前)正向有功费率 3 最大需量及发生时间";
    text_code.append(kDltDataId07_01010400);    // "0x01010400_(当前)正向有功费率 4 最大需量及发生时间";
    text_code.append(kDltDataId07_01010500);    // "0x01010500_(当前)正向有功费率 5 最大需量及发生时间";
    text_code.append(kDltDataId07_01010600);    // "0x01010600_(当前)正向有功费率 6 最大需量及发生时间";
    text_code.append(kDltDataId07_01010700);    // "0x01010700_(当前)正向有功费率 7 最大需量及发生时间";
    text_code.append(kDltDataId07_01010800);    // "0x01010800_(当前)正向有功费率 8 最大需量及发生时间";
    text_code.append(kDltDataId07_01020000);    // "0x01020000_(当前)反向有功总最大需量及发生时间";
    text_code.append(kDltDataId07_01020100);    // "0x01020100_(当前)反向有功费率 1 最大需量及发生时间";
    text_code.append(kDltDataId07_01020200);    // "0x01020200_(当前)反向有功费率 2 最大需量及发生时间";
    text_code.append(kDltDataId07_01020300);    // "0x01020300_(当前)反向有功费率 3 最大需量及发生时间";
    text_code.append(kDltDataId07_01020400);    // "0x01020400_(当前)反向有功费率 4 最大需量及发生时间";
    text_code.append(kDltDataId07_01020500);    // "0x01020500_(当前)反向有功费率 5 最大需量及发生时间";
    text_code.append(kDltDataId07_01020600);    // "0x01020600_(当前)反向有功费率 6 最大需量及发生时间";
    text_code.append(kDltDataId07_01020700);    // "0x01020700_(当前)反向有功费率 7 最大需量及发生时间";
    text_code.append(kDltDataId07_01020800);    // "0x01020800_(当前)反向有功费率 8 最大需量及发生时间";
    text_code.append(kDltDataId07_02010100);    // "0x02010100_A 相电压";
    text_code.append(kDltDataId07_02010200);    // "0x02010200_B 相电压";
    text_code.append(kDltDataId07_02010300);    // "0x02010300_C 相电压";
    text_code.append(kDltDataId07_02020100);    // "0x02020100_A 相电流";
    text_code.append(kDltDataId07_02020200);    // "0x02020200_B 相电流";
    text_code.append(kDltDataId07_02020300);    // "0x02020300_C 相电流";
    text_code.append(kDltDataId07_02030000);    // "0x02030000_瞬时总有功功率";
    text_code.append(kDltDataId07_02030100);    // "0x02030100_瞬时A相有功功率";
    text_code.append(kDltDataId07_02030200);    // "0x02030200_瞬时B相有功功率";
    text_code.append(kDltDataId07_02030300);    // "0x02030300_瞬时C相有功功率";
    text_code.append(kDltDataId07_02040000);    // "0x02040000_瞬时总无功功率";
    text_code.append(kDltDataId07_02040100);    // "0x02040100_瞬时A相无功功率";
    text_code.append(kDltDataId07_02040200);    // "0x02040200_瞬时B相无功功率";
    text_code.append(kDltDataId07_02040300);    // "0x02040300_瞬时C相无功功率";
    text_code.append(kDltDataId07_02050000);    // "0x02050000_瞬时总视在功率";
    text_code.append(kDltDataId07_02050100);    // "0x02050100_瞬时A相视在功率";
    text_code.append(kDltDataId07_02050200);    // "0x02050200_瞬时B相视在功率";
    text_code.append(kDltDataId07_02050300);    // "0x02050300_瞬时C相视在功率";
    text_code.append(kDltDataId07_02060000);    // "0x02060000_总功率因数";
    text_code.append(kDltDataId07_02060100);    // "0x02060100_A相功率因数";
    text_code.append(kDltDataId07_02060200);    // "0x02060200_B相功率因数";
    text_code.append(kDltDataId07_02060300);    // "0x02060300_C相功率因数";
    text_code.append(kDltDataId07_02800002);    // "0x02800002_电网频率";
    text_code.append(kDltDataId07_02800004);    // "0x02800004_当前有功需量";
    text_code.append(kDltDataId07_02800005);    // "0x02800005_当前无功需量";
    QWidgetComBox *item_func_code = new QWidgetComBox(text_code);
    item_func_code->setCurrentText(code);
    dlt645_tab_->setCellWidget(row, kDlt645TabColumnId_DataIdent, item_func_code);
    // ************ 填充列：读取周期 ************
    QTableWidgetItem *item_read_cycle = new QTableWidgetItem(
        QString("%1").arg(read_cycle) );
    dlt645_tab_->setItem(row, kDlt645TabColumnId_ReadCycle, item_read_cycle);
    // ************ 填充列：名称 ************
    QTableWidgetItem *item_name = new QTableWidgetItem(
        QString("%1").arg(name) );
    dlt645_tab_->setItem(row, kDlt645TabColumnId_Name, item_name);
}
