#ifndef APP_H
#define APP_H

#include <QObject>

class App : public QObject
{
    Q_OBJECT
public:
    static const QString PointTableTypeModbus;
    static const QString PointTableTypeDlt645;

    static const QString CommunChTypeModbusRtu;
    static const QString CommunChTypeModbusTcp;
    static const QString CommunChTypeDlt645;

    static const QString CommunDevTypeModbusRtu;
    static const QString CommunDevTypeModbusTcp;
    static const QString CommunDevTypeDlt645;

    // 点表类型
    typedef enum PointTabType {
        kPointTabType_None = 0,
        kPointTabType_Modbus = 1,
        kPointTabType_Dlt645 = 3,
    } PointTabType_E;
    // 通讯通道类型
    typedef enum ChType {
        kChType_None = 0,
        kChType_ModbusRtu = 1,
        kChType_ModbusTcp = 2,
        kChType_Dlt645 = 3,
    } ChType_E;
    // 通讯设备类型
    typedef enum DevType {
        kDevType_None = 0,
        kDevType_ModbusRtu = 1,
        kDevType_ModbusTcp = 2,
        kDevType_Dlt645 = 3,
    } DevType_E;

public:
    // Modbus功能码
    static const QString kModbusFunCode_01H;
    static const QString kModbusFunCode_02H;
    static const QString kModbusFunCode_03H;
    static const QString kModbusFunCode_04H;

    // Modbus数据类型
    static const QString kModbusDateType_U16;
    static const QString kModbusDateType_S16;
    static const QString kModbusDateType_U32;
    static const QString kModbusDateType_S32;
    // DLT645 07数据标识
    static const QString kDltDataId07_00000000;
    static const QString kDltDataId07_00000100;
    static const QString kDltDataId07_00000200;
    static const QString kDltDataId07_00000300;
    static const QString kDltDataId07_00000400;
    static const QString kDltDataId07_00000500;
    static const QString kDltDataId07_00000600;
    static const QString kDltDataId07_00000700;
    static const QString kDltDataId07_00000800;
    //static const QString kDltDataId07_0000FF00;
    static const QString kDltDataId07_00010000;
    static const QString kDltDataId07_00010100;
    static const QString kDltDataId07_00010200;
    static const QString kDltDataId07_00010300;
    static const QString kDltDataId07_00010400;
    static const QString kDltDataId07_00010500;
    static const QString kDltDataId07_00010600;
    static const QString kDltDataId07_00010700;
    static const QString kDltDataId07_00010800;
    //static const QString kDltDataId07_0001FF00;
    static const QString kDltDataId07_00020000;
    static const QString kDltDataId07_00020100;
    static const QString kDltDataId07_00020200;
    static const QString kDltDataId07_00020300;
    static const QString kDltDataId07_00020400;
    static const QString kDltDataId07_00020500;
    static const QString kDltDataId07_00020600;
    static const QString kDltDataId07_00020700;
    static const QString kDltDataId07_00020800;
    //static const QString kDltDataId07_0002FF00;
    static const QString kDltDataId07_01010000;
    static const QString kDltDataId07_01010100;
    static const QString kDltDataId07_01010200;
    static const QString kDltDataId07_01010300;
    static const QString kDltDataId07_01010400;
    static const QString kDltDataId07_01010500;
    static const QString kDltDataId07_01010600;
    static const QString kDltDataId07_01010700;
    static const QString kDltDataId07_01010800;
    //static const QString kDltDataId07_0101FF00;
    static const QString kDltDataId07_01020000;
    static const QString kDltDataId07_01020100;
    static const QString kDltDataId07_01020200;
    static const QString kDltDataId07_01020300;
    static const QString kDltDataId07_01020400;
    static const QString kDltDataId07_01020500;
    static const QString kDltDataId07_01020600;
    static const QString kDltDataId07_01020700;
    static const QString kDltDataId07_01020800;
    //static const QString kDltDataId07_0102FF00;
    static const QString kDltDataId07_02010100;
    static const QString kDltDataId07_02010200;
    static const QString kDltDataId07_02010300;
    //static const QString kDltDataId07_0201FF00;
    static const QString kDltDataId07_02020100;
    static const QString kDltDataId07_02020200;
    static const QString kDltDataId07_02020300;
    //static const QString kDltDataId07_0202FF00;
    static const QString kDltDataId07_02030000;
    static const QString kDltDataId07_02030100;
    static const QString kDltDataId07_02030200;
    static const QString kDltDataId07_02030300;
    //static const QString kDltDataId07_0203FF00;
    static const QString kDltDataId07_02040000;
    static const QString kDltDataId07_02040100;
    static const QString kDltDataId07_02040200;
    static const QString kDltDataId07_02040300;
    //static const QString kDltDataId07_0204FF00;
    static const QString kDltDataId07_02050000;
    static const QString kDltDataId07_02050100;
    static const QString kDltDataId07_02050200;
    static const QString kDltDataId07_02050300;
    //static const QString kDltDataId07_0205FF00;
    static const QString kDltDataId07_02060000;
    static const QString kDltDataId07_02060100;
    static const QString kDltDataId07_02060200;
    static const QString kDltDataId07_02060300;
    //static const QString kDltDataId07_0206FF00;
    static const QString kDltDataId07_02800002;
    static const QString kDltDataId07_02800004;
    static const QString kDltDataId07_02800005;

public:
    explicit App(QObject *parent = nullptr);

    // 点表类型互转
    static QString PointTabTypeId2Str(PointTabType_E type);
    static PointTabType_E PointTabTypeStr2Id(QString type);
    // 通道类型互转
    static QString ChTypeId2Str(ChType_E type);
    static ChType_E ChTypeStr2Id(QString type);
    // 设备类型互换
    static QString DevTypeId2Str(DevType_E type);
    static DevType_E DevTypeStr2Id(QString type);

    // 生成指定长度的随机字符串
    static QString GenerateRandomString(int length);

signals:
};

#endif // APP_H
