#include "app.h"
#include <QRandomGenerator>
#include <QTime>

const QString App::PointTableTypeModbus = "Modbus";
const QString App::PointTableTypeDlt645 = "Dlt645";

const QString App::CommunChTypeModbusRtu = App::PointTableTypeModbus + "Rtu";
const QString App::CommunChTypeModbusTcp = App::PointTableTypeModbus + "Tcp";
const QString App::CommunChTypeDlt645 = App::PointTableTypeDlt645;

const QString App::CommunDevTypeModbusRtu = App::CommunChTypeModbusRtu;
const QString App::CommunDevTypeModbusTcp = App::CommunChTypeModbusTcp;
const QString App::CommunDevTypeDlt645 = App::CommunChTypeDlt645;

// Modbus功能码
const QString App::kModbusFunCode_01H        = "01H";
const QString App::kModbusFunCode_02H        = "02H";
const QString App::kModbusFunCode_03H        = "03H";
const QString App::kModbusFunCode_04H        = "04H";

// Modbus数据类型
const QString App::kModbusDateType_U16       = "U16";
const QString App::kModbusDateType_S16       = "S16";
const QString App::kModbusDateType_U32       = "U32";
const QString App::kModbusDateType_S32       = "S32";
// DLT645 07数据标识
const QString App::kDltDataId07_00000000 = "0x00000000_(当前)组合有功总电能";
const QString App::kDltDataId07_00000100 = "0x00000100_(当前)组合有功费率 1 电能";
const QString App::kDltDataId07_00000200 = "0x00000200_(当前)组合有功费率 2 电能";
const QString App::kDltDataId07_00000300 = "0x00000300_(当前)组合有功费率 3 电能";
const QString App::kDltDataId07_00000400 = "0x00000400_(当前)组合有功费率 4 电能";
const QString App::kDltDataId07_00000500 = "0x00000500_(当前)组合有功费率 5 电能";
const QString App::kDltDataId07_00000600 = "0x00000600_(当前)组合有功费率 6 电能";
const QString App::kDltDataId07_00000700 = "0x00000700_(当前)组合有功费率 7 电能";
const QString App::kDltDataId07_00000800 = "0x00000800_(当前)组合有功费率 8 电能";
//const QString App::kDltDataId07_0000FF00 = "0x0000FF00_(当前)组合有功电能数据块";
const QString App::kDltDataId07_00010000 = "0x00010000_(当前)正向有功总电能";
const QString App::kDltDataId07_00010100 = "0x00010100_(当前)正向有功费率 1 电能";
const QString App::kDltDataId07_00010200 = "0x00010200_(当前)正向有功费率 2 电能";
const QString App::kDltDataId07_00010300 = "0x00010300_(当前)正向有功费率 3 电能";
const QString App::kDltDataId07_00010400 = "0x00010400_(当前)正向有功费率 4 电能";
const QString App::kDltDataId07_00010500 = "0x00010500_(当前)正向有功费率 5 电能";
const QString App::kDltDataId07_00010600 = "0x00010600_(当前)正向有功费率 6 电能";
const QString App::kDltDataId07_00010700 = "0x00010700_(当前)正向有功费率 7 电能";
const QString App::kDltDataId07_00010800 = "0x00010800_(当前)正向有功费率 8 电能";
//const QString App::kDltDataId07_0001FF00 = "0x0001FF00_(当前)正向有功电能数据块";
const QString App::kDltDataId07_00020000 = "0x00020000_(当前)反向有功总电能";
const QString App::kDltDataId07_00020100 = "0x00020100_(当前)反向有功费率 1 电能";
const QString App::kDltDataId07_00020200 = "0x00020200_(当前)反向有功费率 2 电能";
const QString App::kDltDataId07_00020300 = "0x00020300_(当前)反向有功费率 3 电能";
const QString App::kDltDataId07_00020400 = "0x00020400_(当前)反向有功费率 4 电能";
const QString App::kDltDataId07_00020500 = "0x00020500_(当前)反向有功费率 5 电能";
const QString App::kDltDataId07_00020600 = "0x00020600_(当前)反向有功费率 6 电能";
const QString App::kDltDataId07_00020700 = "0x00020700_(当前)反向有功费率 7 电能";
const QString App::kDltDataId07_00020800 = "0x00020800_(当前)反向有功费率 8 电能";
//const QString App::kDltDataId07_0002FF00 = "0x0002FF00_(当前)反向有功电能数据块";
const QString App::kDltDataId07_01010000 = "0x01010000_(当前)正向有功总最大需量及发生时间";
const QString App::kDltDataId07_01010100 = "0x01010100_(当前)正向有功费率 1 最大需量及发生时间";
const QString App::kDltDataId07_01010200 = "0x01010200_(当前)正向有功费率 2 最大需量及发生时间";
const QString App::kDltDataId07_01010300 = "0x01010300_(当前)正向有功费率 3 最大需量及发生时间";
const QString App::kDltDataId07_01010400 = "0x01010400_(当前)正向有功费率 4 最大需量及发生时间";
const QString App::kDltDataId07_01010500 = "0x01010500_(当前)正向有功费率 5 最大需量及发生时间";
const QString App::kDltDataId07_01010600 = "0x01010600_(当前)正向有功费率 6 最大需量及发生时间";
const QString App::kDltDataId07_01010700 = "0x01010700_(当前)正向有功费率 7 最大需量及发生时间";
const QString App::kDltDataId07_01010800 = "0x01010800_(当前)正向有功费率 8 最大需量及发生时间";
//const QString App::kDltDataId07_0101FF00 = "0x0101FF00_(当前)正向有功最大需量及发生时间数据块";
const QString App::kDltDataId07_01020000 = "0x01020000_(当前)反向有功总最大需量及发生时间";
const QString App::kDltDataId07_01020100 = "0x01020100_(当前)反向有功费率 1 最大需量及发生时间";
const QString App::kDltDataId07_01020200 = "0x01020200_(当前)反向有功费率 2 最大需量及发生时间";
const QString App::kDltDataId07_01020300 = "0x01020300_(当前)反向有功费率 3 最大需量及发生时间";
const QString App::kDltDataId07_01020400 = "0x01020400_(当前)反向有功费率 4 最大需量及发生时间";
const QString App::kDltDataId07_01020500 = "0x01020500_(当前)反向有功费率 5 最大需量及发生时间";
const QString App::kDltDataId07_01020600 = "0x01020600_(当前)反向有功费率 6 最大需量及发生时间";
const QString App::kDltDataId07_01020700 = "0x01020700_(当前)反向有功费率 7 最大需量及发生时间";
const QString App::kDltDataId07_01020800 = "0x01020800_(当前)反向有功费率 8 最大需量及发生时间";
//const QString App::kDltDataId07_0102FF00 = "0x0102FF00_(当前)反向有功最大需量及发生时间数据块";
const QString App::kDltDataId07_02010100 = "0x02010100_A 相电压";
const QString App::kDltDataId07_02010200 = "0x02010200_B 相电压";
const QString App::kDltDataId07_02010300 = "0x02010300_C 相电压";
//const QString App::kDltDataId07_0201FF00 = "0x0201FF00_电压数据块(三相电压1帧读回)";
const QString App::kDltDataId07_02020100 = "0x02020100_A 相电流";
const QString App::kDltDataId07_02020200 = "0x02020200_B 相电流";
const QString App::kDltDataId07_02020300 = "0x02020300_C 相电流";
//const QString App::kDltDataId07_0202FF00 = "0x0202FF00_电流数据块(三相电流1帧读回)";
const QString App::kDltDataId07_02030000 = "0x02030000_瞬时总有功功率";
const QString App::kDltDataId07_02030100 = "0x02030100_瞬时A相有功功率";
const QString App::kDltDataId07_02030200 = "0x02030200_瞬时B相有功功率";
const QString App::kDltDataId07_02030300 = "0x02030300_瞬时C相有功功率";
//const QString App::kDltDataId07_0203FF00 = "0x0203FF00_瞬时有功功率数据块(三相有功及总有功1帧读回)";
const QString App::kDltDataId07_02040000 = "0x02040000_瞬时总无功功率";
const QString App::kDltDataId07_02040100 = "0x02040100_瞬时A相无功功率";
const QString App::kDltDataId07_02040200 = "0x02040200_瞬时B相无功功率";
const QString App::kDltDataId07_02040300 = "0x02040300_瞬时C相无功功率";
//const QString App::kDltDataId07_0204FF00 = "0x0204FF00_瞬时无功功率数据块(三相无功及总无功1帧读回)";
const QString App::kDltDataId07_02050000 = "0x02050000_瞬时总视在功率";
const QString App::kDltDataId07_02050100 = "0x02050100_瞬时A相视在功率";
const QString App::kDltDataId07_02050200 = "0x02050200_瞬时B相视在功率";
const QString App::kDltDataId07_02050300 = "0x02050300_瞬时C相视在功率";
//const QString App::kDltDataId07_0205FF00 = "0x0205FF00_瞬时视在功率数据块(三相视在及总视在1帧读回)";
const QString App::kDltDataId07_02060000 = "0x02060000_总功率因数";
const QString App::kDltDataId07_02060100 = "0x02060100_A相功率因数";
const QString App::kDltDataId07_02060200 = "0x02060200_B相功率因数";
const QString App::kDltDataId07_02060300 = "0x02060300_C相功率因数";
//const QString App::kDltDataId07_0206FF00 = "0x0206FF00_功率因数数据块(三相功率因数及总功率因数1帧读回)";
const QString App::kDltDataId07_02800002 = "0x02800002_电网频率";
const QString App::kDltDataId07_02800004 = "0x02800004_当前有功需量";
const QString App::kDltDataId07_02800005 = "0x02800005_当前无功需量";

App::App(QObject *parent)
    : QObject{parent}
{

}

// 点表类型互转
QString App::PointTabTypeId2Str(PointTabType_E type)
{
    switch(type) {
    case kPointTabType_None:
        return "";
    case kPointTabType_Modbus:
        return PointTableTypeModbus;
    case kPointTabType_Dlt645:
        return PointTableTypeDlt645;
    default:
        return "";
    }
}
App::PointTabType_E App::PointTabTypeStr2Id(QString type)
{
    if(type == PointTableTypeModbus) {
        return kPointTabType_Modbus;
    }
    else if(type == PointTableTypeDlt645) {
        return kPointTabType_Dlt645;
    }
    else {
        return kPointTabType_None;
    }
}

// 通道类型互转
QString App::ChTypeId2Str(ChType_E type)
{
    switch(type) {
    case kChType_None:
        return "";
    case kChType_ModbusRtu:
        return CommunChTypeModbusRtu;
    case kChType_ModbusTcp:
        return CommunChTypeModbusTcp;
    case kChType_Dlt645:
        return CommunChTypeDlt645;
    default:
        return "";
    }
}
App::ChType_E App::ChTypeStr2Id(QString type)
{
    if(type == CommunChTypeModbusRtu) {
        return kChType_ModbusRtu;
    }
    else if(type == CommunChTypeModbusTcp) {
        return kChType_ModbusTcp;
    }
    else if(type == CommunChTypeDlt645) {
        return kChType_Dlt645;
    }
    else {
        return kChType_None;
    }
}

// 设备类型互换
QString App::DevTypeId2Str(DevType_E type)
{
    switch(type) {
    case kDevType_None:
        return "";
    case kDevType_ModbusRtu:
        return CommunDevTypeModbusRtu;
    case kDevType_ModbusTcp:
        return CommunDevTypeModbusTcp;
    case kDevType_Dlt645:
        return CommunDevTypeDlt645;
    default:
        return "";
    }
}
App::DevType_E App::DevTypeStr2Id(QString type)
{
    if(type == CommunDevTypeModbusRtu) {
        return kDevType_ModbusRtu;
    }
    else if(type == CommunDevTypeModbusTcp) {
        return kDevType_ModbusTcp;
    }
    else if(type == CommunDevTypeDlt645) {
        return kDevType_Dlt645;
    }
    else {
        return kDevType_None;
    }
}

QString App::GenerateRandomString(int length)
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_");
    QString randomString;
    randomString.reserve(length);

    // 初始化随机数生成器
    QRandomGenerator *generator = QRandomGenerator::global();

    for (int i = 0; i < length; ++i) {
        int index = generator->bounded(possibleCharacters.length());
        randomString.append(possibleCharacters.at(index));
    }

    return randomString;
}
