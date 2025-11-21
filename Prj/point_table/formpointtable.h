#ifndef FORMPOINTTABLE_H
#define FORMPOINTTABLE_H

#include <QWidget>
#include "customtablewidget.h"
#include "app.h"

namespace Ui {
class FormPointTable;
}

class FormPointTable : public QWidget
{
    Q_OBJECT

public:
    // Modbus功能码
    const QString kModbusFunCode_01H        = "01H";
    const QString kModbusFunCode_02H        = "02H";
    const QString kModbusFunCode_03H        = "03H";
    const QString kModbusFunCode_04H        = "04H";

    // Modbus数据类型
    const QString kModbusDateType_U16       = "U16";
    const QString kModbusDateType_S16       = "S16";
    const QString kModbusDateType_U32       = "U32";
    const QString kModbusDateType_S32       = "S32";
    // DLT645 07数据标识
    const QString kDltDataId07_00000000 = "0x00000000_(当前)组合有功总电能";
    const QString kDltDataId07_00000100 = "0x00000100_(当前)组合有功费率 1 电能";
    const QString kDltDataId07_00000200 = "0x00000200_(当前)组合有功费率 2 电能";
    const QString kDltDataId07_00000300 = "0x00000300_(当前)组合有功费率 3 电能";
    const QString kDltDataId07_00000400 = "0x00000400_(当前)组合有功费率 4 电能";
    const QString kDltDataId07_00000500 = "0x00000500_(当前)组合有功费率 5 电能";
    const QString kDltDataId07_00000600 = "0x00000600_(当前)组合有功费率 6 电能";
    const QString kDltDataId07_00000700 = "0x00000700_(当前)组合有功费率 7 电能";
    const QString kDltDataId07_00000800 = "0x00000800_(当前)组合有功费率 8 电能";
    //const QString kDltDataId07_0000FF00 = "0x0000FF00_(当前)组合有功电能数据块";
    const QString kDltDataId07_00010000 = "0x00010000_(当前)正向有功总电能";
    const QString kDltDataId07_00010100 = "0x00010100_(当前)正向有功费率 1 电能";
    const QString kDltDataId07_00010200 = "0x00010200_(当前)正向有功费率 2 电能";
    const QString kDltDataId07_00010300 = "0x00010300_(当前)正向有功费率 3 电能";
    const QString kDltDataId07_00010400 = "0x00010400_(当前)正向有功费率 4 电能";
    const QString kDltDataId07_00010500 = "0x00010500_(当前)正向有功费率 5 电能";
    const QString kDltDataId07_00010600 = "0x00010600_(当前)正向有功费率 6 电能";
    const QString kDltDataId07_00010700 = "0x00010700_(当前)正向有功费率 7 电能";
    const QString kDltDataId07_00010800 = "0x00010800_(当前)正向有功费率 8 电能";
    //const QString kDltDataId07_0001FF00 = "0x0001FF00_(当前)正向有功电能数据块";
    const QString kDltDataId07_00020000 = "0x00020000_(当前)反向有功总电能";
    const QString kDltDataId07_00020100 = "0x00020100_(当前)反向有功费率 1 电能";
    const QString kDltDataId07_00020200 = "0x00020200_(当前)反向有功费率 2 电能";
    const QString kDltDataId07_00020300 = "0x00020300_(当前)反向有功费率 3 电能";
    const QString kDltDataId07_00020400 = "0x00020400_(当前)反向有功费率 4 电能";
    const QString kDltDataId07_00020500 = "0x00020500_(当前)反向有功费率 5 电能";
    const QString kDltDataId07_00020600 = "0x00020600_(当前)反向有功费率 6 电能";
    const QString kDltDataId07_00020700 = "0x00020700_(当前)反向有功费率 7 电能";
    const QString kDltDataId07_00020800 = "0x00020800_(当前)反向有功费率 8 电能";
    //const QString kDltDataId07_0002FF00 = "0x0002FF00_(当前)反向有功电能数据块";
    const QString kDltDataId07_01010000 = "0x01010000_(当前)正向有功总最大需量及发生时间";
    const QString kDltDataId07_01010100 = "0x01010100_(当前)正向有功费率 1 最大需量及发生时间";
    const QString kDltDataId07_01010200 = "0x01010200_(当前)正向有功费率 2 最大需量及发生时间";
    const QString kDltDataId07_01010300 = "0x01010300_(当前)正向有功费率 3 最大需量及发生时间";
    const QString kDltDataId07_01010400 = "0x01010400_(当前)正向有功费率 4 最大需量及发生时间";
    const QString kDltDataId07_01010500 = "0x01010500_(当前)正向有功费率 5 最大需量及发生时间";
    const QString kDltDataId07_01010600 = "0x01010600_(当前)正向有功费率 6 最大需量及发生时间";
    const QString kDltDataId07_01010700 = "0x01010700_(当前)正向有功费率 7 最大需量及发生时间";
    const QString kDltDataId07_01010800 = "0x01010800_(当前)正向有功费率 8 最大需量及发生时间";
    //const QString kDltDataId07_0101FF00 = "0x0101FF00_(当前)正向有功最大需量及发生时间数据块";
    const QString kDltDataId07_01020000 = "0x01020000_(当前)反向有功总最大需量及发生时间";
    const QString kDltDataId07_01020100 = "0x01020100_(当前)反向有功费率 1 最大需量及发生时间";
    const QString kDltDataId07_01020200 = "0x01020200_(当前)反向有功费率 2 最大需量及发生时间";
    const QString kDltDataId07_01020300 = "0x01020300_(当前)反向有功费率 3 最大需量及发生时间";
    const QString kDltDataId07_01020400 = "0x01020400_(当前)反向有功费率 4 最大需量及发生时间";
    const QString kDltDataId07_01020500 = "0x01020500_(当前)反向有功费率 5 最大需量及发生时间";
    const QString kDltDataId07_01020600 = "0x01020600_(当前)反向有功费率 6 最大需量及发生时间";
    const QString kDltDataId07_01020700 = "0x01020700_(当前)反向有功费率 7 最大需量及发生时间";
    const QString kDltDataId07_01020800 = "0x01020800_(当前)反向有功费率 8 最大需量及发生时间";
    //const QString kDltDataId07_0102FF00 = "0x0102FF00_(当前)反向有功最大需量及发生时间数据块";
    const QString kDltDataId07_02010100 = "0x02010100_A 相电压";
    const QString kDltDataId07_02010200 = "0x02010200_B 相电压";
    const QString kDltDataId07_02010300 = "0x02010300_C 相电压";
    //const QString kDltDataId07_0201FF00 = "0x0201FF00_电压数据块(三相电压1帧读回)";
    const QString kDltDataId07_02020100 = "0x02020100_A 相电流";
    const QString kDltDataId07_02020200 = "0x02020200_B 相电流";
    const QString kDltDataId07_02020300 = "0x02020300_C 相电流";
    //const QString kDltDataId07_0202FF00 = "0x0202FF00_电流数据块(三相电流1帧读回)";
    const QString kDltDataId07_02030000 = "0x02030000_瞬时总有功功率";
    const QString kDltDataId07_02030100 = "0x02030100_瞬时A相有功功率";
    const QString kDltDataId07_02030200 = "0x02030200_瞬时B相有功功率";
    const QString kDltDataId07_02030300 = "0x02030300_瞬时C相有功功率";
    //const QString kDltDataId07_0203FF00 = "0x0203FF00_瞬时有功功率数据块(三相有功及总有功1帧读回)";
    const QString kDltDataId07_02040000 = "0x02040000_瞬时总无功功率";
    const QString kDltDataId07_02040100 = "0x02040100_瞬时A相无功功率";
    const QString kDltDataId07_02040200 = "0x02040200_瞬时B相无功功率";
    const QString kDltDataId07_02040300 = "0x02040300_瞬时C相无功功率";
    //const QString kDltDataId07_0204FF00 = "0x0204FF00_瞬时无功功率数据块(三相无功及总无功1帧读回)";
    const QString kDltDataId07_02050000 = "0x02050000_瞬时总视在功率";
    const QString kDltDataId07_02050100 = "0x02050100_瞬时A相视在功率";
    const QString kDltDataId07_02050200 = "0x02050200_瞬时B相视在功率";
    const QString kDltDataId07_02050300 = "0x02050300_瞬时C相视在功率";
    //const QString kDltDataId07_0205FF00 = "0x0205FF00_瞬时视在功率数据块(三相视在及总视在1帧读回)";
    const QString kDltDataId07_02060000 = "0x02060000_总功率因数";
    const QString kDltDataId07_02060100 = "0x02060100_A相功率因数";
    const QString kDltDataId07_02060200 = "0x02060200_B相功率因数";
    const QString kDltDataId07_02060300 = "0x02060300_C相功率因数";
    //const QString kDltDataId07_0206FF00 = "0x0206FF00_功率因数数据块(三相功率因数及总功率因数1帧读回)";
    const QString kDltDataId07_02800002 = "0x02800002_电网频率";
    const QString kDltDataId07_02800004 = "0x02800004_当前有功需量";
    const QString kDltDataId07_02800005 = "0x02800005_当前无功需量";

private:
    // Modbus表格的总列数
    const int kModbusTabColumns             = 6;
    // 每个数据类型的列号(位于表格中的哪一列)
    const int kModbusTabColumnId_StartAddr  = 0;    // 起始地址
    const int kModbusTabColumnId_PointNum   = 1;    // 点数量
    const int kModbusTabColumnId_Code       = 2;    // 功能码
    const int kModbusTabColumnId_DataType   = 3;    // 数据类型
    const int kModbusTabColumnId_ReadCycle  = 4;    // 读取周期
    const int kModbusTabColumnId_Name       = 5;    // 名称

    // Dlt645表格的总列数
    const int kDlt645TabColumns             = 3;
    // 每个数据类型的列号(位于表格中的哪一列)
    const int kDlt645TabColumnId_DataIdent  = 0;    // 数据标识
    const int kDlt645TabColumnId_ReadCycle  = 1;    // 点数量
    const int kDlt645TabColumnId_Name       = 2;    // 功能码

public:
    explicit FormPointTable(App::PointTabType_E type, QWidget *parent = nullptr);
    ~FormPointTable();
    void SetPrjName(const QString &name);

private slots:
    void on_comboBox_Type_currentTextChanged(const QString &arg1);

private:
    // 表格主体初始化
    void TableWidget_Init();
    // 填充一行数据
    void ModbusTableWidget_RowSet(
        int row, quint16 start_addr, quint16 point_num, const QString &code,
        const QString &data_type, int read_cycle, const QString &name);
    // 填充一行数据
    void Dlt645TableWidget_RowSet(
        int row, const QString &code, int read_cycle, const QString &name);

private:
    Ui::FormPointTable *ui;
    App::PointTabType_E type_;
    CustomTableWidget *modbus_tab_ = nullptr;
    CustomTableWidget *dlt645_tab_ = nullptr;
};

#endif // FORMPOINTTABLE_H
