#ifndef JSONPARSE_H
#define JSONPARSE_H

#include <QObject>
#include <QMap>
#include "data_struct/modbuspointstruct.h"
#include "data_struct/dlt645pointstruct.h"
#include "data_struct/modbusrtuchstruct.h"
#include "data_struct/modbustcpchstruct.h"
#include "data_struct/dlt645chstruct.h"
#include "data_struct/modbusrtudevstruct.h"
#include "data_struct/modbustcpdevstruct.h"
#include "data_struct/dlt645devstruct.h"

class JsonParse : public QObject
{
    Q_OBJECT
public:
    explicit JsonParse(QObject *parent = nullptr);

    QMap<QString, ModbusPointStruct::PointTab_T> GetModbusPointTabs();  // Modbus点表
    QMap<QString, Dlt645PointStruct::PointTab_T> GetDlt645PointTabs();  // DLT645点表

    QString GetModbusRtuChFileName();                                   // ModbusRtu通道的文件名
    QString GetModbusTcpChFileName();                                   // ModbusTcp通道的文件名
    QString GetDlt645ChFileName();                                      // DLT645通道的文件名
    QMap<QString, ModbusRtuChStruct::Ch_T> GetModbusRtuChs();           // ModbusRtu通道
    QMap<QString, ModbusTcpChStruct::Ch_T> GetModbusTcpChs();           // ModbusTcp通道
    QMap<QString, Dlt645ChStruct::Ch_T> GetDlt645Chs();                 // DLT645通道

    QString GetModbusRtuDevFileName();                                  // ModbusRtu设备的文件名
    QString GetModbusTcpDevFileName();                                  // ModbusTcp设备的文件名
    QString GetDlt645DevFileName();                                     // DLT645设备的文件名
    QMap<QString, ModbusRtuDevStruct::Dev_T> GetModbusRtuDevs();        // ModbusRtu设备
    QMap<QString, ModbusTcpDevStruct::Dev_T> GetModbusTcpDevs();        // ModbusTcp设备
    QMap<QString, Dlt645DevStruct::Dev_T> GetDlt645Devs();              // DLT645设备

signals:

private:
    QJsonObject JsonFile2JsonObj(const QString &fileName);

    // 解析Index文件
    void ParseIndex(const QString &fileName);
    QMap<QString, QString> ParseObject(const QJsonObject& obj);

    // 解析Modbus点表文件
    ModbusPointStruct::PointTab_T ParseModbusPoint(const QString &fileName);
    QList<ModbusPointStruct::Point_T> ParseModbusPointArray(const QJsonArray &points_array);

    // 解析DLT645点表文件
    Dlt645PointStruct::PointTab_T ParseDlt645Point(const QString &fileName);
    QList<Dlt645PointStruct::Point_T> ParseDlt645PointArray(const QJsonArray &points_array);

    // 解析ModbusRtu通讯通道文件
    QMap<QString, ModbusRtuChStruct::Ch_T> ParseModbusRtuChs(const QString &fileName);
    ModbusRtuChStruct::Ch_T ParseModbusRtuCh(const QJsonObject &chObj);

    // 解析ModbusTcp通讯通道文件
    QMap<QString, ModbusTcpChStruct::Ch_T> ParseModbusTcpChs(const QString &fileName);
    ModbusTcpChStruct::Ch_T ParseModbusTcpCh(const QJsonObject &chObj);

    // 解析Dlt645通讯通道文件
    QMap<QString, Dlt645ChStruct::Ch_T> ParseDlt645Chs(const QString &fileName);
    Dlt645ChStruct::Ch_T ParseDlt645Ch(const QJsonObject &chObj);

    // 解析ModbusRtu通讯设备文件
    QMap<QString, ModbusRtuDevStruct::Dev_T> ParseModbusRtuDevs(const QString &fileName);
    ModbusRtuDevStruct::Dev_T ParseModbusRtuDev(const QJsonObject &chObj);

    // 解析ModbusTcp通讯设备文件
    QMap<QString, ModbusTcpDevStruct::Dev_T> ParseModbusTcpDevs(const QString &fileName);
    ModbusTcpDevStruct::Dev_T ParseModbusTcpDev(const QJsonObject &chObj);

    // 解析Dlt645通讯设备文件
    QMap<QString, Dlt645DevStruct::Dev_T> ParseDlt645Devs(const QString &fileName);
    Dlt645DevStruct::Dev_T ParseDlt645Dev(const QJsonObject &chObj);

private:
    QMap<QString, ModbusPointStruct::PointTab_T> modbusPointTabs_;  // Modbus点表
    QMap<QString, Dlt645PointStruct::PointTab_T> dlt645PointTabs_;  // DLT645点表

    QString modbusRtuChFileName_;                                   // ModbusRtu通道的文件名
    QString modbusTcpChFileName_;                                   // ModbusTcp通道的文件名
    QString dlt645ChFileName_;                                      // DLT645通道的文件名
    QMap<QString, ModbusRtuChStruct::Ch_T> modbusRtuChs_;           // ModbusRtu通道
    QMap<QString, ModbusTcpChStruct::Ch_T> modbusTcpChs_;           // ModbusTcp通道
    QMap<QString, Dlt645ChStruct::Ch_T> dlt645Chs_;                 // DLT645通道

    QString modbusRtuDevFileName_;                                  // ModbusRtu设备的文件名
    QString modbusTcpDevFileName_;                                  // ModbusTcp设备的文件名
    QString dlt645DevFileName_;                                     // DLT645设备的文件名
    QMap<QString, ModbusRtuDevStruct::Dev_T> modbusRtuDevs_;        // ModbusRtu设备
    QMap<QString, ModbusTcpDevStruct::Dev_T> modbusTcpDevs_;        // ModbusTcp设备
    QMap<QString, Dlt645DevStruct::Dev_T> dlt645Devs_;              // DLT645设备
};

#endif // JSONPARSE_H
