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

signals:
};

#endif // APP_H
