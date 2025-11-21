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
