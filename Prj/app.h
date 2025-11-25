#ifndef APP_H
#define APP_H

#include <QObject>
#include <QSettings>

class App : public QObject
{
    Q_OBJECT
public:
    static const QString kStrPrjName;               // 工程名KEY
    static const QString kStrPointTable;            // 点表KEY
    static const QString kStrCommunCh;              // 通讯通道KEY
    static const QString kStrCommunDev;             // 通讯设备KEY

    static const QString kStrPointTableTypeModbus;
    static const QString kStrPointTableTypeDlt645;

    static const QString kStrCommunChTypeModbusRtu;
    static const QString kStrCommunChTypeModbusTcp;
    static const QString kStrCommunChTypeDlt645;

    static const QString kStrCommunDevTypeModbusRtu;
    static const QString kStrCommunDevTypeModbusTcp;
    static const QString kStrCommunDevTypeDlt645;

    static const QString kStrPointTableModbusName;
    static const QString kStrPointTableModbusPoint;
    static const QString kStrPointTableDlt645Name;
    static const QString kStrPointTableDlt645Point;

    static const QString kStrChModbusRtuChannel;
    static const QString kStrChModbusRtuName;
    static const QString kStrChModbusRtuInterface;
    static const QString kStrChModbusRtuBaudRate;
    static const QString kStrChModbusRtuDataBits;
    static const QString kStrChModbusRtuStopBits;
    static const QString kStrChModbusRtuParity;

    static const QString kStrChModbusTcpChannel;
    static const QString kStrChModbusTcpName;
    static const QString kStrChModbusTcpIp;
    static const QString kStrChModbusTcpPort;

    static const QString kStrChDlt645Channel;
    static const QString kStrChDlt645Name;
    static const QString kStrChDlt645Interface;
    static const QString kStrChDlt645BaudRate;
    static const QString kStrChDlt645DataBits;
    static const QString kStrChDlt645StopBits;
    static const QString kStrChDlt645Parity;

    static const QString kStrDevModbusRtuDevice;
    static const QString kStrDevModbusRtuName;
    static const QString kStrDevModbusRtuChannel;
    static const QString kStrDevModbusRtuPointTable;
    static const QString kStrDevModbusRtuAddress;

    static const QString kStrDevModbusTcpDevice;
    static const QString kStrDevModbusTcpName;
    static const QString kStrDevModbusTcpChannel;
    static const QString kStrDevModbusTcpPointTable;
    static const QString kStrDevModbusTcpAddress;

    static const QString kStrDevDlt645Device;
    static const QString kStrDevDlt645Name;
    static const QString kStrDevDlt645Channel;
    static const QString kStrDevDlt645PointTable;
    static const QString kStrDevDlt645Address;

    static QSettings settings;
    static const QString kImportFileName;

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
    static const QString kStrModbusFunCode_01H;
    static const QString kStrModbusFunCode_02H;
    static const QString kStrModbusFunCode_03H;
    static const QString kStrModbusFunCode_04H;

    // Modbus数据类型
    static const QString kStrModbusDateType_U16;
    static const QString kStrModbusDateType_S16;
    static const QString kStrModbusDateType_U32;
    static const QString kStrModbusDateType_S32;
    // DLT645 07数据标识
    static const QString kStrDltDataId07_00000000;
    static const QString kStrDltDataId07_00000100;
    static const QString kStrDltDataId07_00000200;
    static const QString kStrDltDataId07_00000300;
    static const QString kStrDltDataId07_00000400;
    static const QString kStrDltDataId07_00000500;
    static const QString kStrDltDataId07_00000600;
    static const QString kStrDltDataId07_00000700;
    static const QString kStrDltDataId07_00000800;
    //static const QString kStrDltDataId07_0000FF00;
    static const QString kStrDltDataId07_00010000;
    static const QString kStrDltDataId07_00010100;
    static const QString kStrDltDataId07_00010200;
    static const QString kStrDltDataId07_00010300;
    static const QString kStrDltDataId07_00010400;
    static const QString kStrDltDataId07_00010500;
    static const QString kStrDltDataId07_00010600;
    static const QString kStrDltDataId07_00010700;
    static const QString kStrDltDataId07_00010800;
    //static const QString kStrDltDataId07_0001FF00;
    static const QString kStrDltDataId07_00020000;
    static const QString kStrDltDataId07_00020100;
    static const QString kStrDltDataId07_00020200;
    static const QString kStrDltDataId07_00020300;
    static const QString kStrDltDataId07_00020400;
    static const QString kStrDltDataId07_00020500;
    static const QString kStrDltDataId07_00020600;
    static const QString kStrDltDataId07_00020700;
    static const QString kStrDltDataId07_00020800;
    //static const QString kStrDltDataId07_0002FF00;
    static const QString kStrDltDataId07_01010000;
    static const QString kStrDltDataId07_01010100;
    static const QString kStrDltDataId07_01010200;
    static const QString kStrDltDataId07_01010300;
    static const QString kStrDltDataId07_01010400;
    static const QString kStrDltDataId07_01010500;
    static const QString kStrDltDataId07_01010600;
    static const QString kStrDltDataId07_01010700;
    static const QString kStrDltDataId07_01010800;
    //static const QString kStrDltDataId07_0101FF00;
    static const QString kStrDltDataId07_01020000;
    static const QString kStrDltDataId07_01020100;
    static const QString kStrDltDataId07_01020200;
    static const QString kStrDltDataId07_01020300;
    static const QString kStrDltDataId07_01020400;
    static const QString kStrDltDataId07_01020500;
    static const QString kStrDltDataId07_01020600;
    static const QString kStrDltDataId07_01020700;
    static const QString kStrDltDataId07_01020800;
    //static const QString kStrDltDataId07_0102FF00;
    static const QString kStrDltDataId07_02010100;
    static const QString kStrDltDataId07_02010200;
    static const QString kStrDltDataId07_02010300;
    //static const QString kStrDltDataId07_0201FF00;
    static const QString kStrDltDataId07_02020100;
    static const QString kStrDltDataId07_02020200;
    static const QString kStrDltDataId07_02020300;
    //static const QString kStrDltDataId07_0202FF00;
    static const QString kStrDltDataId07_02030000;
    static const QString kStrDltDataId07_02030100;
    static const QString kStrDltDataId07_02030200;
    static const QString kStrDltDataId07_02030300;
    //static const QString kStrDltDataId07_0203FF00;
    static const QString kStrDltDataId07_02040000;
    static const QString kStrDltDataId07_02040100;
    static const QString kStrDltDataId07_02040200;
    static const QString kStrDltDataId07_02040300;
    //static const QString kStrDltDataId07_0204FF00;
    static const QString kStrDltDataId07_02050000;
    static const QString kStrDltDataId07_02050100;
    static const QString kStrDltDataId07_02050200;
    static const QString kStrDltDataId07_02050300;
    //static const QString kStrDltDataId07_0205FF00;
    static const QString kStrDltDataId07_02060000;
    static const QString kStrDltDataId07_02060100;
    static const QString kStrDltDataId07_02060200;
    static const QString kStrDltDataId07_02060300;
    //static const QString kStrDltDataId07_0206FF00;
    static const QString kStrDltDataId07_02800002;
    static const QString kStrDltDataId07_02800004;
    static const QString kStrDltDataId07_02800005;

public:
    // Modbus表格的总列数
    static const int kModbusTabColumns;
    // 每个数据类型的列号(位于表格中的哪一列)
    static const int kModbusTabColumnId_StartAddr;  // 起始地址
    static const int kModbusTabColumnId_PointNum;   // 点数量
    static const int kModbusTabColumnId_Code;       // 功能码
    static const int kModbusTabColumnId_DataType;   // 数据类型
    static const int kModbusTabColumnId_ReadCycle;  // 读取周期
    static const int kModbusTabColumnId_Name;       // 名称

    // Dlt645表格的总列数
    static const int kDlt645TabColumns;
    // 每个数据类型的列号(位于表格中的哪一列)
    static const int kDlt645TabColumnId_DataIdent;  // 数据标识
    static const int kDlt645TabColumnId_ReadCycle;  // 点数量
    static const int kDlt645TabColumnId_Name;       // 功能码

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
