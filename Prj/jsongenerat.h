#ifndef JSONGENERAT_H
#define JSONGENERAT_H

#include <QObject>
#include <QMap>
#include <QJsonDocument>
#include <QDir>
#include "data_struct/modbuspointstruct.h"
#include "data_struct/dlt645pointstruct.h"
#include "data_struct/modbusrtuchstruct.h"
#include "data_struct/modbustcpchstruct.h"
#include "data_struct/dlt645chstruct.h"
#include "data_struct/modbusrtudevstruct.h"
#include "data_struct/modbustcpdevstruct.h"
#include "data_struct/dlt645devstruct.h"

class JsonGenerate : public QObject
{
    Q_OBJECT
public:
    explicit JsonGenerate(
        const QString &folder,
        QMap<QString, ModbusPointStruct::PointTab_T> &mpts, // Modbus点表
        QMap<QString, Dlt645PointStruct::PointTab_T> &dpts, // DLT645点表
        QMap<QString, ModbusRtuChStruct::Ch_T> &mrcs,       // ModbusRtu通道
        QMap<QString, ModbusTcpChStruct::Ch_T> &mtcs,       // ModbusTcp通道
        QMap<QString, Dlt645ChStruct::Ch_T> &dlcs,          // DLT645通道
        QMap<QString, ModbusRtuDevStruct::Dev_T> &mrds,     // ModbusRtu设备
        QMap<QString, ModbusTcpDevStruct::Dev_T> &mtds,     // ModbusTcp设备
        QMap<QString, Dlt645DevStruct::Dev_T> &dlds,        // DLT645设备
        bool debug = false,
        QObject *parent = nullptr);

private:
    // 将JSON写入到文件中保存
    bool JsonOjbSaveFile(const QJsonObject obj, const QString fileName,
                         QJsonDocument::JsonFormat forma = QJsonDocument::Compact,
                         bool debug = false);

    // 生成Modbus点表文件
    QString GenerateModbusPoint(const ModbusPointStruct::PointTab_T &pointTab,
                                QJsonDocument::JsonFormat forma = QJsonDocument::Compact,
                                bool debug = false);
    QJsonArray GenerateModbusPointArray(const QList<ModbusPointStruct::Point_T> &points);

    // 生成DLT645点表文件
    QString GenerateDlt645Point(const Dlt645PointStruct::PointTab_T &pointTab,
                                QJsonDocument::JsonFormat forma = QJsonDocument::Compact,
                                bool debug = false);
    QJsonArray GenerateDlt645PointArray(const QList<Dlt645PointStruct::Point_T> &points);

    // 生成ModbusRtu通讯通道文件
    QString GenerateModbusRtuChs(const QMap<QString, ModbusRtuChStruct::Ch_T> &chs,
                                 QJsonDocument::JsonFormat forma = QJsonDocument::Compact,
                                 bool debug = false);
    QJsonObject GenerateModbusRtuCh(const ModbusRtuChStruct::Ch_T &ch);

    // 生成ModbusTcp通讯通道文件
    QString GenerateModbusTcpChs(const QMap<QString, ModbusTcpChStruct::Ch_T> &chs,
                                 QJsonDocument::JsonFormat forma = QJsonDocument::Compact,
                                 bool debug = false);
    QJsonObject GenerateModbusTcpCh(const ModbusTcpChStruct::Ch_T &ch);

    // 生成Dlt645通讯通道文件
    QString GenerateDlt645Chs(const QMap<QString, Dlt645ChStruct::Ch_T> &chs,
                              QJsonDocument::JsonFormat forma = QJsonDocument::Compact,
                              bool debug = false);
    QJsonObject GenerateDlt645Ch(const Dlt645ChStruct::Ch_T &ch);

    // 生成ModbusRtu通讯设备文件
    QString GenerateModbusRtuDevs(const QMap<QString, ModbusRtuDevStruct::Dev_T> &devs,
                                  QJsonDocument::JsonFormat forma = QJsonDocument::Compact,
                                  bool debug = false);
    QJsonObject GenerateModbusRtuDev(const ModbusRtuDevStruct::Dev_T &dev);

    // 生成ModbusTcp通讯设备文件
    QString GenerateModbusTcpDevs(const QMap<QString, ModbusTcpDevStruct::Dev_T> &devs,
                                  QJsonDocument::JsonFormat forma = QJsonDocument::Compact,
                                  bool debug = false);
    QJsonObject GenerateModbusTcpDev(const ModbusTcpDevStruct::Dev_T &dev);

    // 生成Dlt645通讯设备文件
    QString GenerateDlt645Devs(const QMap<QString, Dlt645DevStruct::Dev_T> &devs,
                               QJsonDocument::JsonFormat forma = QJsonDocument::Compact,
                               bool debug = false);
    QJsonObject GenerateDlt645Dev(const Dlt645DevStruct::Dev_T &dev);

    // 生成Index文件
    QString GenerateIndex(QJsonDocument::JsonFormat forma = QJsonDocument::Compact,
        bool debug = false);

signals:

private:
    QString folder_;                                                // 文件夹
    QDir dir_;                                                      // 使用 QDir 对象进行拼接

    QMap<QString, QString> modbusPointTabFileNames_;                // Modbus点表文件名
    QMap<QString, QString> dlt645PointTabFileNames_;                // DLT645点表文件名
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

    const QString kStrPointTabFileNamePrefixModbus = "point_tab_modbus_";
    const QString kStrPointTabFileNamePrefixDlt645 = "point_tab_dlt645_";
    const QString kStrCommunChFileNameModbusRtu    = "commun_ch_modbusrtu";
    const QString kStrCommunChFileNameModbusTcp    = "commun_ch_modbustcp";
    const QString kStrCommunChFileNameDlt645       = "commun_ch_dlt645";
    const QString kStrCommunDevFileNameModbusRtu   = "commun_ch_modbusrtu";
    const QString kStrCommunDevFileNameModbusTcp   = "commun_ch_modbustcp";
    const QString kStrCommunDevFileNameDlt645      = "commun_ch_dlt645";
    const QString kStrIndexFileName                = "index";
    const QString kStrFileFormat                   = ".json";
};

#endif // JSONGENERAT_H
