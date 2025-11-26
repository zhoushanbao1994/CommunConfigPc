#include "app.h"
#include <QRandomGenerator>
#include <QTime>

const QString App::kStrPrjName    = "name";
const QString App::kStrPointTable = "point_table";
const QString App::kStrCommunCh   = "commun_channel";
const QString App::kStrCommunDev  = "commun_dev";

const QString App::kStrPointTableTypeModbus = "modbus";
const QString App::kStrPointTableTypeDlt645 = "dlt645";

const QString App::kStrCommunChTypeModbusRtu = App::kStrPointTableTypeModbus + "rtu";
const QString App::kStrCommunChTypeModbusTcp = App::kStrPointTableTypeModbus + "tcp";
const QString App::kStrCommunChTypeDlt645    = App::kStrPointTableTypeDlt645;

const QString App::kStrCommunDevTypeModbusRtu = App::kStrCommunChTypeModbusRtu;
const QString App::kStrCommunDevTypeModbusTcp = App::kStrCommunChTypeModbusTcp;
const QString App::kStrCommunDevTypeDlt645    = App::kStrCommunChTypeDlt645   ;

const QString App::kStrPointTableModbusName       = "name"       ;
const QString App::kStrPointTableModbusCustomName = "custom_name";
const QString App::kStrPointTableModbusPoint      = "point"      ;
const QString App::kStrPointTableDlt645Name       = App::kStrPointTableModbusName      ;
const QString App::kStrPointTableDlt645CustomName = App::kStrPointTableModbusCustomName;
const QString App::kStrPointTableDlt645Point      = App::kStrPointTableModbusPoint     ;

const QString App::kStrChModbusRtuChannel    = "channel"    ;
const QString App::kStrChModbusRtuName       = "name"       ;
const QString App::kStrChModbusRtuCustomName = "custom_name";
const QString App::kStrChModbusRtuInterface  = "interface"  ;
const QString App::kStrChModbusRtuBaudRate   = "baud"       ;
const QString App::kStrChModbusRtuDataBits   = "data"       ;
const QString App::kStrChModbusRtuStopBits   = "stop"       ;
const QString App::kStrChModbusRtuParity     = "check"      ;

const QString App::kStrChModbusTcpChannel    = App::kStrChModbusRtuChannel   ;
const QString App::kStrChModbusTcpName       = App::kStrChModbusRtuName      ;
const QString App::kStrChModbusTcpCustomName = App::kStrChModbusRtuCustomName;
const QString App::kStrChModbusTcpIp         = "ip"  ;
const QString App::kStrChModbusTcpPort       = "port";

const QString App::kStrChDlt645Channel    = App::kStrChModbusRtuChannel   ;
const QString App::kStrChDlt645Name       = App::kStrChModbusRtuName      ;
const QString App::kStrChDlt645CustomName = App::kStrChModbusRtuCustomName;
const QString App::kStrChDlt645Interface  = App::kStrChModbusRtuInterface ;
const QString App::kStrChDlt645BaudRate   = App::kStrChModbusRtuBaudRate  ;
const QString App::kStrChDlt645DataBits   = App::kStrChModbusRtuDataBits  ;
const QString App::kStrChDlt645StopBits   = App::kStrChModbusRtuStopBits  ;
const QString App::kStrChDlt645Parity     = App::kStrChModbusRtuParity    ;

const QString App::kStrDevModbusRtuDevice     = "dev"        ;
const QString App::kStrDevModbusRtuName       = "name"       ;
const QString App::kStrDevModbusRtuCustomName = "custom_name";
const QString App::kStrDevModbusRtuChannel    = "ch"         ;
const QString App::kStrDevModbusRtuPointTable = "point"      ;
const QString App::kStrDevModbusRtuAddress    = "addr"       ;

const QString App::kStrDevModbusTcpDevice     = App::kStrDevModbusRtuDevice    ;
const QString App::kStrDevModbusTcpName       = App::kStrDevModbusRtuName      ;
const QString App::kStrDevModbusTcpCustomName = App::kStrDevModbusRtuCustomName;
const QString App::kStrDevModbusTcpChannel    = App::kStrDevModbusRtuChannel   ;
const QString App::kStrDevModbusTcpPointTable = App::kStrDevModbusRtuPointTable;
const QString App::kStrDevModbusTcpAddress    = App::kStrDevModbusRtuAddress   ;

const QString App::kStrDevDlt645Device     = App::kStrDevModbusRtuDevice    ;
const QString App::kStrDevDlt645Name       = App::kStrDevModbusRtuName      ;
const QString App::kStrDevDlt645CustomName = App::kStrDevModbusRtuCustomName;
const QString App::kStrDevDlt645Channel    = App::kStrDevModbusRtuChannel   ;
const QString App::kStrDevDlt645PointTable = App::kStrDevModbusRtuPointTable;
const QString App::kStrDevDlt645Address    = App::kStrDevModbusRtuAddress   ;

QSettings App::settings = QSettings("config.ini", QSettings::IniFormat);
const QString App::kImportFileName = "ImportFileName";


// Modbus功能码
const QString App::kStrModbusFunCode_01H        = "01H";
const QString App::kStrModbusFunCode_02H        = "02H";
const QString App::kStrModbusFunCode_03H        = "03H";
const QString App::kStrModbusFunCode_04H        = "04H";

// Modbus数据类型
const QString App::kStrModbusDateType_U16       = "U16";
const QString App::kStrModbusDateType_S16       = "S16";
const QString App::kStrModbusDateType_U32       = "U32";
const QString App::kStrModbusDateType_S32       = "S32";
// DLT645 07数据标识
const QString App::kStrDltDataId07_00000000 = "0x00000000_(当前)组合有功总电能";
const QString App::kStrDltDataId07_00000100 = "0x00000100_(当前)组合有功费率 1 电能";
const QString App::kStrDltDataId07_00000200 = "0x00000200_(当前)组合有功费率 2 电能";
const QString App::kStrDltDataId07_00000300 = "0x00000300_(当前)组合有功费率 3 电能";
const QString App::kStrDltDataId07_00000400 = "0x00000400_(当前)组合有功费率 4 电能";
const QString App::kStrDltDataId07_00000500 = "0x00000500_(当前)组合有功费率 5 电能";
const QString App::kStrDltDataId07_00000600 = "0x00000600_(当前)组合有功费率 6 电能";
const QString App::kStrDltDataId07_00000700 = "0x00000700_(当前)组合有功费率 7 电能";
const QString App::kStrDltDataId07_00000800 = "0x00000800_(当前)组合有功费率 8 电能";
//const QString App::kStrDltDataId07_0000FF00 = "0x0000FF00_(当前)组合有功电能数据块";
const QString App::kStrDltDataId07_00010000 = "0x00010000_(当前)正向有功总电能";
const QString App::kStrDltDataId07_00010100 = "0x00010100_(当前)正向有功费率 1 电能";
const QString App::kStrDltDataId07_00010200 = "0x00010200_(当前)正向有功费率 2 电能";
const QString App::kStrDltDataId07_00010300 = "0x00010300_(当前)正向有功费率 3 电能";
const QString App::kStrDltDataId07_00010400 = "0x00010400_(当前)正向有功费率 4 电能";
const QString App::kStrDltDataId07_00010500 = "0x00010500_(当前)正向有功费率 5 电能";
const QString App::kStrDltDataId07_00010600 = "0x00010600_(当前)正向有功费率 6 电能";
const QString App::kStrDltDataId07_00010700 = "0x00010700_(当前)正向有功费率 7 电能";
const QString App::kStrDltDataId07_00010800 = "0x00010800_(当前)正向有功费率 8 电能";
//const QString App::kStrDltDataId07_0001FF00 = "0x0001FF00_(当前)正向有功电能数据块";
const QString App::kStrDltDataId07_00020000 = "0x00020000_(当前)反向有功总电能";
const QString App::kStrDltDataId07_00020100 = "0x00020100_(当前)反向有功费率 1 电能";
const QString App::kStrDltDataId07_00020200 = "0x00020200_(当前)反向有功费率 2 电能";
const QString App::kStrDltDataId07_00020300 = "0x00020300_(当前)反向有功费率 3 电能";
const QString App::kStrDltDataId07_00020400 = "0x00020400_(当前)反向有功费率 4 电能";
const QString App::kStrDltDataId07_00020500 = "0x00020500_(当前)反向有功费率 5 电能";
const QString App::kStrDltDataId07_00020600 = "0x00020600_(当前)反向有功费率 6 电能";
const QString App::kStrDltDataId07_00020700 = "0x00020700_(当前)反向有功费率 7 电能";
const QString App::kStrDltDataId07_00020800 = "0x00020800_(当前)反向有功费率 8 电能";
//const QString App::kStrDltDataId07_0002FF00 = "0x0002FF00_(当前)反向有功电能数据块";
const QString App::kStrDltDataId07_01010000 = "0x01010000_(当前)正向有功总最大需量及发生时间";
const QString App::kStrDltDataId07_01010100 = "0x01010100_(当前)正向有功费率 1 最大需量及发生时间";
const QString App::kStrDltDataId07_01010200 = "0x01010200_(当前)正向有功费率 2 最大需量及发生时间";
const QString App::kStrDltDataId07_01010300 = "0x01010300_(当前)正向有功费率 3 最大需量及发生时间";
const QString App::kStrDltDataId07_01010400 = "0x01010400_(当前)正向有功费率 4 最大需量及发生时间";
const QString App::kStrDltDataId07_01010500 = "0x01010500_(当前)正向有功费率 5 最大需量及发生时间";
const QString App::kStrDltDataId07_01010600 = "0x01010600_(当前)正向有功费率 6 最大需量及发生时间";
const QString App::kStrDltDataId07_01010700 = "0x01010700_(当前)正向有功费率 7 最大需量及发生时间";
const QString App::kStrDltDataId07_01010800 = "0x01010800_(当前)正向有功费率 8 最大需量及发生时间";
//const QString App::kStrDltDataId07_0101FF00 = "0x0101FF00_(当前)正向有功最大需量及发生时间数据块";
const QString App::kStrDltDataId07_01020000 = "0x01020000_(当前)反向有功总最大需量及发生时间";
const QString App::kStrDltDataId07_01020100 = "0x01020100_(当前)反向有功费率 1 最大需量及发生时间";
const QString App::kStrDltDataId07_01020200 = "0x01020200_(当前)反向有功费率 2 最大需量及发生时间";
const QString App::kStrDltDataId07_01020300 = "0x01020300_(当前)反向有功费率 3 最大需量及发生时间";
const QString App::kStrDltDataId07_01020400 = "0x01020400_(当前)反向有功费率 4 最大需量及发生时间";
const QString App::kStrDltDataId07_01020500 = "0x01020500_(当前)反向有功费率 5 最大需量及发生时间";
const QString App::kStrDltDataId07_01020600 = "0x01020600_(当前)反向有功费率 6 最大需量及发生时间";
const QString App::kStrDltDataId07_01020700 = "0x01020700_(当前)反向有功费率 7 最大需量及发生时间";
const QString App::kStrDltDataId07_01020800 = "0x01020800_(当前)反向有功费率 8 最大需量及发生时间";
//const QString App::kStrDltDataId07_0102FF00 = "0x0102FF00_(当前)反向有功最大需量及发生时间数据块";
const QString App::kStrDltDataId07_02010100 = "0x02010100_A 相电压";
const QString App::kStrDltDataId07_02010200 = "0x02010200_B 相电压";
const QString App::kStrDltDataId07_02010300 = "0x02010300_C 相电压";
//const QString App::kStrDltDataId07_0201FF00 = "0x0201FF00_电压数据块(三相电压1帧读回)";
const QString App::kStrDltDataId07_02020100 = "0x02020100_A 相电流";
const QString App::kStrDltDataId07_02020200 = "0x02020200_B 相电流";
const QString App::kStrDltDataId07_02020300 = "0x02020300_C 相电流";
//const QString App::kStrDltDataId07_0202FF00 = "0x0202FF00_电流数据块(三相电流1帧读回)";
const QString App::kStrDltDataId07_02030000 = "0x02030000_瞬时总有功功率";
const QString App::kStrDltDataId07_02030100 = "0x02030100_瞬时A相有功功率";
const QString App::kStrDltDataId07_02030200 = "0x02030200_瞬时B相有功功率";
const QString App::kStrDltDataId07_02030300 = "0x02030300_瞬时C相有功功率";
//const QString App::kStrDltDataId07_0203FF00 = "0x0203FF00_瞬时有功功率数据块(三相有功及总有功1帧读回)";
const QString App::kStrDltDataId07_02040000 = "0x02040000_瞬时总无功功率";
const QString App::kStrDltDataId07_02040100 = "0x02040100_瞬时A相无功功率";
const QString App::kStrDltDataId07_02040200 = "0x02040200_瞬时B相无功功率";
const QString App::kStrDltDataId07_02040300 = "0x02040300_瞬时C相无功功率";
//const QString App::kStrDltDataId07_0204FF00 = "0x0204FF00_瞬时无功功率数据块(三相无功及总无功1帧读回)";
const QString App::kStrDltDataId07_02050000 = "0x02050000_瞬时总视在功率";
const QString App::kStrDltDataId07_02050100 = "0x02050100_瞬时A相视在功率";
const QString App::kStrDltDataId07_02050200 = "0x02050200_瞬时B相视在功率";
const QString App::kStrDltDataId07_02050300 = "0x02050300_瞬时C相视在功率";
//const QString App::kStrDltDataId07_0205FF00 = "0x0205FF00_瞬时视在功率数据块(三相视在及总视在1帧读回)";
const QString App::kStrDltDataId07_02060000 = "0x02060000_总功率因数";
const QString App::kStrDltDataId07_02060100 = "0x02060100_A相功率因数";
const QString App::kStrDltDataId07_02060200 = "0x02060200_B相功率因数";
const QString App::kStrDltDataId07_02060300 = "0x02060300_C相功率因数";
//const QString App::kStrDltDataId07_0206FF00 = "0x0206FF00_功率因数数据块(三相功率因数及总功率因数1帧读回)";
const QString App::kStrDltDataId07_02800002 = "0x02800002_电网频率";
const QString App::kStrDltDataId07_02800004 = "0x02800004_当前有功需量";
const QString App::kStrDltDataId07_02800005 = "0x02800005_当前无功需量";

// Modbus表格的总列数
const int App::kModbusTabColumns             = 6;
// 每个数据类型的列号(位于表格中的哪一列)
const int App::kModbusTabColumnId_StartAddr  = 0;    // 起始地址
const int App::kModbusTabColumnId_PointNum   = 1;    // 点数量
const int App::kModbusTabColumnId_Code       = 2;    // 功能码
const int App::kModbusTabColumnId_DataType   = 3;    // 数据类型
const int App::kModbusTabColumnId_ReadCycle  = 4;    // 读取周期
const int App::kModbusTabColumnId_Name       = 5;    // 名称

// Dlt645表格的总列数
const int App::kDlt645TabColumns             = 3;
// 每个数据类型的列号(位于表格中的哪一列)
const int App::kDlt645TabColumnId_DataIdent  = 0;    // 数据标识
const int App::kDlt645TabColumnId_ReadCycle  = 1;    // 点数量
const int App::kDlt645TabColumnId_Name       = 2;    // 功能码


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
        return kStrPointTableTypeModbus;
    case kPointTabType_Dlt645:
        return kStrPointTableTypeDlt645;
    default:
        return "";
    }
}
App::PointTabType_E App::PointTabTypeStr2Id(QString type)
{
    if(type == kStrPointTableTypeModbus) {
        return kPointTabType_Modbus;
    }
    else if(type == kStrPointTableTypeDlt645) {
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
        return kStrCommunChTypeModbusRtu;
    case kChType_ModbusTcp:
        return kStrCommunChTypeModbusTcp;
    case kChType_Dlt645:
        return kStrCommunChTypeDlt645;
    default:
        return "";
    }
}
App::ChType_E App::ChTypeStr2Id(QString type)
{
    if(type == kStrCommunChTypeModbusRtu) {
        return kChType_ModbusRtu;
    }
    else if(type == kStrCommunChTypeModbusTcp) {
        return kChType_ModbusTcp;
    }
    else if(type == kStrCommunChTypeDlt645) {
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
        return kStrCommunDevTypeModbusRtu;
    case kDevType_ModbusTcp:
        return kStrCommunDevTypeModbusTcp;
    case kDevType_Dlt645:
        return kStrCommunDevTypeDlt645;
    default:
        return "";
    }
}
App::DevType_E App::DevTypeStr2Id(QString type)
{
    if(type == kStrCommunDevTypeModbusRtu) {
        return kDevType_ModbusRtu;
    }
    else if(type == kStrCommunDevTypeModbusTcp) {
        return kDevType_ModbusTcp;
    }
    else if(type == kStrCommunDevTypeDlt645) {
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

/**
 * @brief 将字符串转换为数字，自动识别十进制和十六进制（0x开头）
 * @param str 输入的字符串
 * @param ok 输出参数，转换成功为 true，失败为 false
 * @return 转换后的数字（qlonglong 类型，可根据需要修改）
 */
qlonglong App::StringToNumber(const QString& str, bool& ok)
{
    ok = false;
    if (str.isEmpty()) {
        return 0; // 空字符串，转换失败
    }

    // 去除字符串两端的空白字符（处理可能的空格）
    QString trimmedStr = str.trimmed();

    // 判断是否为十六进制（以 0x 或 0X 开头）
    if (trimmedStr.startsWith(QLatin1String("0x"), Qt::CaseInsensitive)) {
        // 十六进制转换，基数为 16
        return trimmedStr.toLongLong(&ok, 16);
    } else {
        // 十进制转换，基数为 10
        return trimmedStr.toLongLong(&ok, 10);
    }
}

// Modbus功能码格式化
QString App::ModbusCodeFormatting(QString code)
{
    if((code == "1") || (code == "0x1") || (code == "0x01") || (code == "1H") || (code == "01H")) {
        return kStrModbusFunCode_01H;
    }
    else if((code == "2") || (code == "0x2") || (code == "0x02") || (code == "2H") || (code == "02H")) {
        return kStrModbusFunCode_02H;
    }
    else if((code == "3") || (code == "0x3") || (code == "0x03") || (code == "3H") || (code == "03H")) {
        return kStrModbusFunCode_03H;
    }
    else if((code == "4") || (code == "0x4") || (code == "0x04") || (code == "4H") || (code == "04H")) {
        return kStrModbusFunCode_04H;
    }
    else {
        return kStrModbusFunCode_03H;
    }
}
// Modbus数据类型格式化
QString App::ModbusDataTypeFormatting(QString type)
{
    if((type == "U16") || (type == "u16")) {
        return kStrModbusDateType_U16;
    }
    else if((type == "S16") || (type == "s16")) {
        return kStrModbusDateType_S16;
    }
    else if((type == "U32") || (type == "u32")) {
        return kStrModbusDateType_U32;
    }
    else if((type == "S32") || (type == "s32")) {
        return kStrModbusDateType_S32;
    }
    else {
        return kStrModbusDateType_U16;
    }
}

// DLT645数据标识格式化
QString App::ModbusDataIdentFormatting(QString ident)
{
    if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00000000, 10)) {  //"0x00000000_(当前)组合有功总电能";
        return kStrDltDataId07_00000000; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00000100, 10)) {  //"0x00000100_(当前)组合有功费率 1 电能";
        return kStrDltDataId07_00000100; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00000200, 10)) {  //"0x00000200_(当前)组合有功费率 2 电能";
        return kStrDltDataId07_00000200; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00000300, 10)) {  //"0x00000300_(当前)组合有功费率 3 电能";
        return kStrDltDataId07_00000300; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00000400, 10)) {  //"0x00000400_(当前)组合有功费率 4 电能";
        return kStrDltDataId07_00000400; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00000500, 10)) {  //"0x00000500_(当前)组合有功费率 5 电能";
        return kStrDltDataId07_00000500; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00000600, 10)) {  //"0x00000600_(当前)组合有功费率 6 电能";
        return kStrDltDataId07_00000600; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00000700, 10)) {  //"0x00000700_(当前)组合有功费率 7 电能";
        return kStrDltDataId07_00000700; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00000800, 10)) {  //"0x00000800_(当前)组合有功费率 8 电能";
        return kStrDltDataId07_00000800; }
    //else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_0000FF00, 10)) {  //"0x0000FF00_(当前)组合有功电能数据块";
    //    return kStrDltDataId07_0000FF00; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00010000, 10)) {  //"0x00010000_(当前)正向有功总电能";
        return kStrDltDataId07_00010000; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00010100, 10)) {  //"0x00010100_(当前)正向有功费率 1 电能";
        return kStrDltDataId07_00010100; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00010200, 10)) {  //"0x00010200_(当前)正向有功费率 2 电能";
        return kStrDltDataId07_00010200; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00010300, 10)) {  //"0x00010300_(当前)正向有功费率 3 电能";
        return kStrDltDataId07_00010300; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00010400, 10)) {  //"0x00010400_(当前)正向有功费率 4 电能";
        return kStrDltDataId07_00010400; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00010500, 10)) {  //"0x00010500_(当前)正向有功费率 5 电能";
        return kStrDltDataId07_00010500; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00010600, 10)) {  //"0x00010600_(当前)正向有功费率 6 电能";
        return kStrDltDataId07_00010600; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00010700, 10)) {  //"0x00010700_(当前)正向有功费率 7 电能";
        return kStrDltDataId07_00010700; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00010800, 10)) {  //"0x00010800_(当前)正向有功费率 8 电能";
        return kStrDltDataId07_00010800; }
    //else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_0001FF00, 10)) {  //"0x0001FF00_(当前)正向有功电能数据块";
    //    return kStrDltDataId07_0001FF00; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00020000, 10)) {  //"0x00020000_(当前)反向有功总电能";
        return kStrDltDataId07_00020000; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00020100, 10)) {  //"0x00020100_(当前)反向有功费率 1 电能";
        return kStrDltDataId07_00020100; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00020200, 10)) {  //"0x00020200_(当前)反向有功费率 2 电能";
        return kStrDltDataId07_00020200; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00020300, 10)) {  //"0x00020300_(当前)反向有功费率 3 电能";
        return kStrDltDataId07_00020300; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00020400, 10)) {  //"0x00020400_(当前)反向有功费率 4 电能";
        return kStrDltDataId07_00020400; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00020500, 10)) {  //"0x00020500_(当前)反向有功费率 5 电能";
        return kStrDltDataId07_00020500; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00020600, 10)) {  //"0x00020600_(当前)反向有功费率 6 电能";
        return kStrDltDataId07_00020600; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00020700, 10)) {  //"0x00020700_(当前)反向有功费率 7 电能";
        return kStrDltDataId07_00020700; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_00020800, 10)) {  //"0x00020800_(当前)反向有功费率 8 电能";
        return kStrDltDataId07_00020800; }
    //else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_0002FF00, 10)) {  //"0x0002FF00_(当前)反向有功电能数据块";
    //    return kStrDltDataId07_0002FF00; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01010000, 10)) {  //"0x01010000_(当前)正向有功总最大需量及发生时间";
        return kStrDltDataId07_01010000; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01010100, 10)) {  //"0x01010100_(当前)正向有功费率 1 最大需量及发生时间";
        return kStrDltDataId07_01010100; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01010200, 10)) {  //"0x01010200_(当前)正向有功费率 2 最大需量及发生时间";
        return kStrDltDataId07_01010200; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01010300, 10)) {  //"0x01010300_(当前)正向有功费率 3 最大需量及发生时间";
        return kStrDltDataId07_01010300; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01010400, 10)) {  //"0x01010400_(当前)正向有功费率 4 最大需量及发生时间";
        return kStrDltDataId07_01010400; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01010500, 10)) {  //"0x01010500_(当前)正向有功费率 5 最大需量及发生时间";
        return kStrDltDataId07_01010500; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01010600, 10)) {  //"0x01010600_(当前)正向有功费率 6 最大需量及发生时间";
        return kStrDltDataId07_01010600; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01010700, 10)) {  //"0x01010700_(当前)正向有功费率 7 最大需量及发生时间";
        return kStrDltDataId07_01010700; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01010800, 10)) {  //"0x01010800_(当前)正向有功费率 8 最大需量及发生时间";
        return kStrDltDataId07_01010800; }
    //else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_0101FF00, 10)) {  //"0x0101FF00_(当前)正向有功最大需量及发生时间数据块";
    //    return kStrDltDataId07_0101FF00; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01020000, 10)) {  //"0x01020000_(当前)反向有功总最大需量及发生时间";
        return kStrDltDataId07_01020000; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01020100, 10)) {  //"0x01020100_(当前)反向有功费率 1 最大需量及发生时间";
        return kStrDltDataId07_01020100; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01020200, 10)) {  //"0x01020200_(当前)反向有功费率 2 最大需量及发生时间";
        return kStrDltDataId07_01020200; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01020300, 10)) {  //"0x01020300_(当前)反向有功费率 3 最大需量及发生时间";
        return kStrDltDataId07_01020300; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01020400, 10)) {  //"0x01020400_(当前)反向有功费率 4 最大需量及发生时间";
        return kStrDltDataId07_01020400; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01020500, 10)) {  //"0x01020500_(当前)反向有功费率 5 最大需量及发生时间";
        return kStrDltDataId07_01020500; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01020600, 10)) {  //"0x01020600_(当前)反向有功费率 6 最大需量及发生时间";
        return kStrDltDataId07_01020600; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01020700, 10)) {  //"0x01020700_(当前)反向有功费率 7 最大需量及发生时间";
        return kStrDltDataId07_01020700; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_01020800, 10)) {  //"0x01020800_(当前)反向有功费率 8 最大需量及发生时间";
        return kStrDltDataId07_01020800; }
    //else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_0102FF00, 10)) {  //"0x0102FF00_(当前)反向有功最大需量及发生时间数据块";
    //    return kStrDltDataId07_0102FF00; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02010100, 10)) {  //"0x02010100_A 相电压";
        return kStrDltDataId07_02010100; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02010200, 10)) {  //"0x02010200_B 相电压";
        return kStrDltDataId07_02010200; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02010300, 10)) {  //"0x02010300_C 相电压";
        return kStrDltDataId07_02010300; }
    //else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_0201FF00, 10)) {  //"0x0201FF00_电压数据块(三相电压1帧读回)";
    //    return kStrDltDataId07_0201FF00; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02020100, 10)) {  //"0x02020100_A 相电流";
        return kStrDltDataId07_02020100; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02020200, 10)) {  //"0x02020200_B 相电流";
        return kStrDltDataId07_02020200; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02020300, 10)) {  //"0x02020300_C 相电流";
        return kStrDltDataId07_02020300; }
    //else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_0202FF00, 10)) {  //"0x0202FF00_电流数据块(三相电流1帧读回)";
    //    return kStrDltDataId07_0202FF00; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02030000, 10)) {  //"0x02030000_瞬时总有功功率";
        return kStrDltDataId07_02030000; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02030100, 10)) {  //"0x02030100_瞬时A相有功功率";
        return kStrDltDataId07_02030100; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02030200, 10)) {  //"0x02030200_瞬时B相有功功率";
        return kStrDltDataId07_02030200; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02030300, 10)) {  //"0x02030300_瞬时C相有功功率";
        return kStrDltDataId07_02030300; }
    //else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_0203FF00, 10)) {  //"0x0203FF00_有功功率数据块(三相有功功率1帧读回)";
    //    return kStrDltDataId07_0203FF00; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02040000, 10)) {  //"0x02040000_瞬时总无功功率";
        return kStrDltDataId07_02040000; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02040100, 10)) {  //"0x02040100_瞬时A相无功功率";
        return kStrDltDataId07_02040100; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02040200, 10)) {  //"0x02040200_瞬时B相无功功率";
        return kStrDltDataId07_02040200; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02040300, 10)) {  //"0x02040300_瞬时C相无功功率";
        return kStrDltDataId07_02040300; }
    //else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_0204FF00, 10)) {  //"0x0204FF00_无功功率数据块(三相无功功率1帧读回)";
    //    return kStrDltDataId07_0204FF00; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02050000, 10)) {  //"0x02050000_瞬时总功率因数";
        return kStrDltDataId07_02050000; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02050100, 10)) {  //"0x02050100_瞬时A相功率因数";
        return kStrDltDataId07_02050100; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02050200, 10)) {  //"0x02050200_瞬时B相功率因数";
        return kStrDltDataId07_02050200; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02050300, 10)) {  //"0x02050300_瞬时C相功率因数";
        return kStrDltDataId07_02050300; }
    //else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_0205FF00, 10)) {  //"0x0205FF00_功率因数数据块(三相功率因数1帧读回)";
    //    return kStrDltDataId07_0205FF00; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02060000, 10)) {  //"0x02060000_瞬时总视在功率";
        return kStrDltDataId07_02060000; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02060100, 10)) {  //"0x02060100_瞬时A相视在功率";
        return kStrDltDataId07_02060100; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02060200, 10)) {  //"0x02060200_瞬时B相视在功率";
        return kStrDltDataId07_02060200; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02060300, 10)) {  //"0x02060300_瞬时C相视在功率";
        return kStrDltDataId07_02060300; }
    //else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_0206FF00, 10)) {  //"0x0206FF00_视在功率数据块(三相视在功率1帧读回)";
    //    return kStrDltDataId07_0206FF00; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02800002, 10)) {  //"0x02800002_电网频率";
        return kStrDltDataId07_02800002; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02800004, 10)) {  //"0x02800004_当前有功需量";
        return kStrDltDataId07_02800004; }
    else if(compareFirstNIgnoreCase(ident, kStrDltDataId07_02800005, 10)) {  //"0x02800005_当前无功需量";
        return kStrDltDataId07_02800005; }
    else {
        return kStrDltDataId07_00000000;
    }
}

// 不区分大小写，比较字符串前n个字符是否一致 1-一致；0-不一致；
bool App::compareFirstNIgnoreCase(const QString &str1, const QString &str2, int n)
{
    return str1.leftRef(n).compare(str2.leftRef(n), Qt::CaseInsensitive) == 0;
}

// 校验位标识格式化
QString App::ParityFormatting(QString parity)
{
    if((parity == "None") || (parity == "none") || (parity == "N") || (parity == "n")) {
        return "None";
    }
    else if((parity == "Even") || (parity == "even") || (parity == "E") || (parity == "e")) {
        return "Even";
    }
    else if((parity == "Odd") || (parity == "odd") || (parity == "O") || (parity == "o")) {
        return "Odd";
    }
    else {
        return "None";
    }
}

// 比较指定字符前的字符串是否一致（默认区分大小写）
bool App::compareBeforeChar(const QString &str1, const QString &str2,
                              QChar delimiter, Qt::CaseSensitivity caseSensitive)
{
    QString s1 = str1.section(delimiter, 0, 0);
    QString s2 = str2.section(delimiter, 0, 0);

    return s1.compare(s2, caseSensitive) == 0;
}

// 设置QCombobox的选项
bool App::SetComboBoxCurrentText(QComboBox *comboBox, const QString &text, QChar delimiter)
{
    // 获取项数
    int count = comboBox->count();
    // 项数为0，直接返回false
    if(count <= 0) {
        return false;
    }

    // 遍历所有选项文本
    for (int i = 0; i < count; ++i) {
        QString itemTtext = comboBox->itemText(i); // 获取第i项的文本
        if(compareBeforeChar(text, itemTtext, delimiter) != true) {
            continue;
        }
        // 找到前缀相同的项，设置未找到的项
        comboBox->setCurrentText(itemTtext);
        return true;
    }
    // 未找到相同的项，设置为第0项
    comboBox->setCurrentIndex(0);
    return false;
}

