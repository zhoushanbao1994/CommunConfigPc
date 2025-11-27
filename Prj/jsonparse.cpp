#include "jsonparse.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QMessageBox>
#include <qDebug>
#include <QFileDialog>
#include <QDir>
#include "app.h"

JsonParse::JsonParse(QObject *parent)
    : QObject{parent}
{
    modbusPointTabs_.clear();       // Modbus点表
    dlt645PointTabs_.clear();       // DLT645点表
    modbusRtuChFileName_ = "";      // ModbusRtu通道的文件名
    modbusTcpChFileName_ = "";      // ModbusTcp通道的文件名
    dlt645ChFileName_ = "";         // DLT645通道的文件名
    modbusRtuDevFileName_ = "";     // ModbusRtu设备的文件名
    modbusTcpDevFileName_ = "";     // ModbusTcp设备的文件名
    dlt645DevFileName_ = "";        // DLT645设备的文件名

    QString path = App::settings.value(App::kImportFileName, QDir::homePath()).toString();
    // 1. 弹出文件对话框，选择 JSON 文件
    QString fileName = QFileDialog::getOpenFileName(
        nullptr,                   // 父窗口
        "选择JSON文件",              // 标题
        path,                       // 默认目录（用户主目录）
        "JSON文件 (*.json);;所有文件 (*)" // 过滤器
        );

    // 判断用户是否选择了文件
    if (fileName.isEmpty()) {
        qDebug() << "用户取消了选择";
        return;
    }
    qDebug() << "选中的文件路径：" << fileName;
    App::settings.setValue(App::kImportFileName, fileName);

    // 解析index文件
    ParseIndex(fileName);
}

// Modbus点表
QMap<QString, ModbusPointStruct::PointTab_T> JsonParse::GetModbusPointTabs()
{
    return modbusPointTabs_;
}
// DLT645点表
QMap<QString, Dlt645PointStruct::PointTab_T> JsonParse::GetDlt645PointTabs()
{
    return dlt645PointTabs_;
}
// ModbusRtu通道的文件名
QString JsonParse::GetModbusRtuChFileName()
{
    return modbusRtuChFileName_;
}
// ModbusTcp通道的文件名
QString JsonParse::GetModbusTcpChFileName()
{
    return modbusTcpChFileName_;
}
// DLT645通道的文件名
QString JsonParse::GetDlt645ChFileName()
{
    return dlt645ChFileName_;
}
// ModbusRtu通道
QMap<QString, ModbusRtuChStruct::Ch_T> JsonParse::GetModbusRtuChs()
{
    return modbusRtuChs_;
}
// ModbusTcp通道
QMap<QString, ModbusTcpChStruct::Ch_T> JsonParse::GetModbusTcpChs()
{
    return modbusTcpChs_;
}
// DLT645通道
QMap<QString, Dlt645ChStruct::Ch_T> JsonParse::GetDlt645Chs()
{
    return dlt645Chs_;
}
// ModbusRtu设备的文件名
QString JsonParse::GetModbusRtuDevFileName()
{
    return modbusRtuDevFileName_;
}
// ModbusTcp设备的文件名
QString JsonParse::GetModbusTcpDevFileName()
{
    return modbusTcpDevFileName_;
}
// DLT645设备的文件名
QString JsonParse::GetDlt645DevFileName()
{
    return dlt645DevFileName_;
}
// ModbusRtu设备
QMap<QString, ModbusRtuDevStruct::Dev_T> JsonParse::GetModbusRtuDevs()
{
    return modbusRtuDevs_;
}
// ModbusTcp设备
QMap<QString, ModbusTcpDevStruct::Dev_T> JsonParse::GetModbusTcpDevs()
{
    return modbusTcpDevs_;
}
// DLT645设备
QMap<QString, Dlt645DevStruct::Dev_T> JsonParse::GetDlt645Devs()
{
    return dlt645Devs_;
}


QJsonObject JsonParse::JsonFile2JsonObj(const QString &fileName)
{
    // 读取文件内容
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "文件打开失败",
                              QString("无法打开文件：%1\n错误信息：%2")
                                  .arg(fileName, file.errorString()));
        return QJsonObject();
    }

    QByteArray jsonData = file.readAll();
    file.close(); // 读取完成后关闭文件

    // 解析 JSON 文档
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    // 检查解析错误
    if (parseError.error != QJsonParseError::NoError) {
        QMessageBox::critical(nullptr, "JSON 解析失败",
                              QString("错误位置：%1\n错误信息：%2")
                                  .arg(parseError.offset)
                                  .arg(parseError.errorString()));
        return QJsonObject();
    }

    // 处理 JSON 对象（如果是数组，逻辑类似）
    if (!jsonDoc.isObject()) {
        QMessageBox::warning(nullptr, "格式警告", "JSON 文档不是对象类型");
        return QJsonObject();
    }

    QJsonObject rootObj = jsonDoc.object();
    return rootObj;
}

// 解析Index文件
void JsonParse::ParseIndex(const QString &fileName)
{
    QJsonObject rootObj = JsonFile2JsonObj(fileName);
    if(rootObj.isEmpty()) {
        return;
    }

    // 创建 QFileInfo 对象
    QFileInfo fileInfo(fileName);
    // 拆分路径和文件名
    QString directoryTmpPath = fileInfo.path();
    //QString fileTmpName = fileInfo.fileName();
    // 使用 QDir 对象进行拼接
    QDir dir(directoryTmpPath);

    // 读取 JSON 中的数据
    qDebug() << "=== JSON 解析结果 ===";
    // 名称
    if (rootObj.contains(App::kStrPrjName) && rootObj[App::kStrPrjName].isString()) {
        qDebug() << "名称：" << rootObj[App::kStrPrjName].toString();
    }
    // 点表
    if (rootObj.contains(App::kStrPointTable) && rootObj[App::kStrPointTable].isObject()) {
        QJsonObject pointObj = rootObj[App::kStrPointTable].toObject();
        // 点表Modbus
        if(pointObj.contains(App::kStrPointTableTypeModbus) && pointObj[App::kStrPointTableTypeModbus].isObject()) {
            QJsonObject pointModbusObj = pointObj[App::kStrPointTableTypeModbus].toObject();
            qDebug() << "通讯点表" << App::kStrPointTableTypeModbus;
            QMap<QString, QString> fileNames = ParseObject(pointModbusObj);
            QMap<QString, QString>::const_iterator it;
            ModbusPointStruct::PointTab_T pointTab;
            for (it = fileNames.cbegin(); it != fileNames.cend(); ++it) {
                qDebug() << "key:" << it.key() << ", 文件名:" << it.value();
                // 解析Modbus点表文件
                pointTab = ParseModbusPoint(dir.filePath(it.value()));
                // 将点表信息记录到Map容器中
                modbusPointTabs_.insert(it.key(), pointTab);
                qDebug() << "Modbus点表名称：" << pointTab.name << ", 自定义名称：" << pointTab.customName;
                for(auto &it : pointTab.points) {
                    qDebug() << "    " << QString("起始地址:0x%1, 点位数量:%2, 功能码:%3, 数据类型:%4, 读取周期:%5, 名称:%6")
                        .arg(it.startAddr, 4, 16, QChar('0')).arg(it.pointNum, 4, 16, QChar('0')).arg(it.code, it.dataType)
                        .arg(it.readCycle).arg(it.customName);
                }
            }
        }
        // 点表Dlt645
        if(pointObj.contains(App::kStrPointTableTypeDlt645) && pointObj[App::kStrPointTableTypeDlt645].isObject()) {
            QJsonObject pointDlt645Obj = pointObj[App::kStrPointTableTypeDlt645].toObject();
            qDebug() << "通讯点表" << App::kStrPointTableTypeDlt645;
            QMap<QString, QString> fileNames = ParseObject(pointDlt645Obj);
            QMap<QString, QString>::const_iterator it;
            Dlt645PointStruct::PointTab_T pointTab;
            for (it = fileNames.cbegin(); it != fileNames.cend(); ++it) {
                qDebug() << "key:" << it.key() << ", 文件名:" << it.value();
                // 解析DLT645点表文件
                pointTab = ParseDlt645Point(dir.filePath(it.value()));
                // 将点表信息记录到Map容器中
                dlt645PointTabs_.insert(it.key(), pointTab);
                qDebug() << "Dlt645点表名称：" << pointTab.name << ", 自定义名称：" << pointTab.customName;
                for(auto &it : pointTab.points) {
                    qDebug() << "    " << QString("数据标识:%1, 读取周期:%2, 名称:%3")
                              .arg(it.dataIdent).arg(it.readCycle).arg(it.customName);
                }
            }
        }
    }
    // 通讯通道
    if (rootObj.contains(App::kStrCommunCh) && rootObj[App::kStrCommunCh].isObject()) {
        QJsonObject chObj = rootObj[App::kStrCommunCh].toObject();
        // 通讯通道ModbusRtu
        if(chObj.contains(App::kStrCommunChTypeModbusRtu) && chObj[App::kStrCommunChTypeModbusRtu].isString()) {
            modbusRtuChFileName_ = chObj[App::kStrCommunChTypeModbusRtu].toString();
            qDebug() << "通讯通道" << App::kStrCommunChTypeModbusRtu << ":" << modbusRtuChFileName_;
            // 解析ModbusRtu通讯通道文件
            modbusRtuChs_ = ParseModbusRtuChs(dir.filePath(modbusRtuChFileName_));
            QMap<QString, ModbusRtuChStruct::Ch_T>::const_iterator it;
            for (it = modbusRtuChs_.cbegin(); it != modbusRtuChs_.cend(); ++it) {
                QString name = it.key();
                ModbusRtuChStruct::Ch_T ch = it.value();
                qDebug() << "    通讯通道名称:" << name << ", 自定义名称：" << ch.customName << ", 通讯通道信息:"
                         << ch.interface << ch.baudRate << ch.dataBits << ch.parity << ch.stopBits;
            }
        }
        // 通讯通道ModbusTcp
        if(chObj.contains(App::kStrCommunChTypeModbusTcp) && chObj[App::kStrCommunChTypeModbusTcp].isString()) {
            modbusTcpChFileName_ = chObj[App::kStrCommunChTypeModbusTcp].toString();
            qDebug() << "通讯通道" << App::kStrCommunChTypeModbusTcp << ":" << modbusTcpChFileName_;
            // 解析ModbusTcp通讯通道文件
            modbusTcpChs_ = ParseModbusTcpChs(dir.filePath(modbusTcpChFileName_));
            QMap<QString, ModbusTcpChStruct::Ch_T>::const_iterator it;
            for (it = modbusTcpChs_.cbegin(); it != modbusTcpChs_.cend(); ++it) {
                QString name = it.key();
                ModbusTcpChStruct::Ch_T ch = it.value();
                qDebug() << "    通讯通道名称:" << name << ", 自定义名称：" << ch.customName << ", 通讯通道信息:" << ch.ip << ch.port;
            }
        }
        // 通讯通道Dlt645
        if(chObj.contains(App::kStrCommunChTypeDlt645) && chObj[App::kStrCommunChTypeDlt645].isString()) {
            dlt645ChFileName_ = chObj[App::kStrCommunChTypeDlt645].toString();
            qDebug() << "通讯通道" << App::kStrCommunChTypeDlt645 << ":" << dlt645ChFileName_;
            // 解析Dlt645通讯通道文件
            dlt645Chs_ = ParseDlt645Chs(dir.filePath(dlt645ChFileName_));
            QMap<QString, Dlt645ChStruct::Ch_T>::const_iterator it;
            for (it = dlt645Chs_.cbegin(); it != dlt645Chs_.cend(); ++it) {
                QString name = it.key();
                Dlt645ChStruct::Ch_T ch = it.value();
                qDebug() << "    通讯通道名称:" << name << ", 自定义名称：" << ch.customName << ", 通讯通道信息:"
                         << ch.interface << ch.baudRate << ch.dataBits << ch.parity << ch.stopBits;
            }
        }
    }
    // 通讯设备
    if (rootObj.contains(App::kStrCommunDev) && rootObj[App::kStrCommunDev].isObject()) {
        QJsonObject devObj = rootObj[App::kStrCommunDev].toObject();
        // 通讯设备ModbusRtu
        if(devObj.contains(App::kStrCommunDevTypeModbusRtu) && devObj[App::kStrCommunDevTypeModbusRtu].isString()) {
            modbusRtuDevFileName_ = devObj[App::kStrCommunDevTypeModbusRtu].toString();
            qDebug() << "通讯设备" << App::kStrCommunDevTypeModbusRtu << ":" << modbusRtuDevFileName_;
            // 解析ModbusRtu通讯设备文件
            modbusRtuDevs_ = ParseModbusRtuDevs(dir.filePath(modbusRtuDevFileName_));
            QMap<QString, ModbusRtuDevStruct::Dev_T>::const_iterator it;
            for (it = modbusRtuDevs_.cbegin(); it != modbusRtuDevs_.cend(); ++it) {
                QString name = it.key();
                ModbusRtuDevStruct::Dev_T dev = it.value();
                qDebug() << "    通讯设备名称:" << name << ", 自定义名称：" << dev.customName << ", 通讯设备信息:"
                         << dev.channelPrjName << dev.pointTablePrjName << dev.address;
            }
        }
        // 通讯设备ModbusTcp
        if(devObj.contains(App::kStrCommunDevTypeModbusTcp) && devObj[App::kStrCommunDevTypeModbusTcp].isString()) {
            modbusTcpDevFileName_ = devObj[App::kStrCommunDevTypeModbusTcp].toString();
            qDebug() << "通讯设备" << App::kStrCommunDevTypeModbusTcp << ":" << modbusTcpDevFileName_;
            // 解析ModbusTcp通讯设备文件
            modbusTcpDevs_ = ParseModbusTcpDevs(dir.filePath(modbusTcpDevFileName_));
            QMap<QString, ModbusTcpDevStruct::Dev_T>::const_iterator it;
            for (it = modbusTcpDevs_.cbegin(); it != modbusTcpDevs_.cend(); ++it) {
                QString name = it.key();
                ModbusTcpDevStruct::Dev_T dev = it.value();
                qDebug() << "    通讯设备名称:" << name << ", 自定义名称：" << dev.customName << ", 通讯设备信息:"
                         << dev.channelPrjName << dev.pointTablePrjName << dev.address;
            }
        }
        // 通讯设备Dlt645
        if(devObj.contains(App::kStrCommunDevTypeDlt645) && devObj[App::kStrCommunDevTypeDlt645].isString()) {
            dlt645DevFileName_ = devObj[App::kStrCommunDevTypeDlt645].toString();
            qDebug() << "通讯设备" << App::kStrCommunDevTypeDlt645 << ":" << dlt645DevFileName_;
            // 解析Dlt645通讯设备文件
            dlt645Devs_ = ParseDlt645Devs(dir.filePath(dlt645DevFileName_));
            QMap<QString, Dlt645DevStruct::Dev_T>::const_iterator it;
            for (it = dlt645Devs_.cbegin(); it != dlt645Devs_.cend(); ++it) {
                QString name = it.key();
                Dlt645DevStruct::Dev_T dev = it.value();
                qDebug() << "    通讯设备名称:" << name << ", 自定义名称：" << dev.customName << ", 通讯设备信息:"
                         << dev.channelPrjName << dev.pointTablePrjName << dev.address;
            }
        }
    }

    qDebug() << __FUNCTION__ << __LINE__ <<  "解析成功: JSON 文件解析完成，详情见调试输出！";
    //QMessageBox::information(nullptr, "解析成功", "JSON 文件解析完成，详情见调试输出！");
}

QMap<QString, QString> JsonParse::ParseObject(const QJsonObject& obj)
{
    QMap<QString, QString> keyValue;

    QStringList keys = obj.keys();
    foreach (const QString &key, keys) {
        if(obj[key].isString()) {
            QString value = obj[key].toString();
            keyValue.insert(key, value);
            qDebug() << "    字段名:" << key << ", 值:" << value;
        }
        else {
            qDebug() << "    字段名:" << key << ", 值类型未知";
        }
    }

    return keyValue;
}


// 解析Modbus点表文件
ModbusPointStruct::PointTab_T JsonParse::ParseModbusPoint(const QString &fileName)
{
    QJsonObject rootObj = JsonFile2JsonObj(fileName);
    if(rootObj.isEmpty()) {
        return ModbusPointStruct::PointTab_T();
    }

    ModbusPointStruct::PointTab_T pointTab;
    // 文件名
    pointTab.fileName = fileName;
    // 名称
    if (rootObj.contains(App::kStrPointTableModbusName) && rootObj[App::kStrPointTableModbusName].isString()) {
        pointTab.name = rootObj[App::kStrPointTableModbusName].toString();
    }
    // 自定义名称
    if (rootObj.contains(App::kStrPointTableModbusCustomName) && rootObj[App::kStrPointTableModbusCustomName].isString()) {
        pointTab.customName = rootObj[App::kStrPointTableModbusCustomName].toString();
    }
    // 点表
    if (rootObj.contains(App::kStrPointTableModbusPoint) && rootObj[App::kStrPointTableModbusPoint].isArray()) {
        QJsonArray pointsArray = rootObj[App::kStrPointTableModbusPoint].toArray();
        pointTab.points = ParseModbusPointArray(pointsArray);
    }

    return pointTab;
}

QList<ModbusPointStruct::Point_T> JsonParse::ParseModbusPointArray(const QJsonArray &pointsArray)
{
    bool ok;
    QList<ModbusPointStruct::Point_T> list;
    for (int i = 0; i < pointsArray.size(); ++i) {
        QJsonValue value = pointsArray.at(i); // 获取第 i 个元素
        if(value.isArray() != true) {
            continue;
        }
        QJsonArray pointArray = value.toArray();
        // 判断数组大小
        if(pointArray.size() != App::kModbusTabColumns) {
            continue;
        }
        // 定义一个点结构
        ModbusPointStruct::Point_T mps;
        // 起始地址
        QJsonValue jsonStartAddr = pointArray.at(App::kModbusTabColumnId_StartAddr);
        if(jsonStartAddr.isString()) {
            mps.startAddr = App::StringToNumber(jsonStartAddr.toString(), ok);
        }
        // 点数量
        QJsonValue jsonPointNum = pointArray.at(App::kModbusTabColumnId_PointNum);
        if(jsonPointNum.isString()) {
            mps.pointNum = App::StringToNumber(jsonPointNum.toString(), ok);
        }
        // 功能码
        QJsonValue jsonCode = pointArray.at(App::kModbusTabColumnId_Code);
        if(jsonCode.isString()) {
            mps.code = jsonCode.toString();
        }
        // 数据类型
        QJsonValue jsonDataType = pointArray.at(App::kModbusTabColumnId_DataType);
        if(jsonDataType.isString()) {
            mps.dataType = jsonDataType.toString();
        }
        // 读取周期
        QJsonValue jsonReadCycle = pointArray.at(App::kModbusTabColumnId_ReadCycle);
        if(jsonReadCycle.isDouble()) {    // Qt5.9及以下只有isDouble，没有isInt
            mps.readCycle = jsonReadCycle.toInt();
        }
        // 名称
        QJsonValue jsonName = pointArray.at(App::kModbusTabColumnId_Name);
        if(jsonName.isString()) {
            mps.customName = jsonName.toString();
        }
        // 将点结构记录到list中
        list.append(mps);
    }

    return list;
}

// 解析DLT645点表文件
Dlt645PointStruct::PointTab_T JsonParse::ParseDlt645Point(const QString &fileName)
{
    QJsonObject rootObj = JsonFile2JsonObj(fileName);
    if(rootObj.isEmpty()) {
        return Dlt645PointStruct::PointTab_T();
    }

    Dlt645PointStruct::PointTab_T pointTab;
    // 文件名
    pointTab.fileName = fileName;
    // 名称
    if (rootObj.contains(App::kStrPointTableDlt645Name) && rootObj[App::kStrPointTableDlt645Name].isString()) {
        pointTab.name = rootObj[App::kStrPointTableDlt645Name].toString();
    }
    // 自定义名称
    if (rootObj.contains(App::kStrPointTableDlt645CustomName) && rootObj[App::kStrPointTableDlt645CustomName].isString()) {
        pointTab.customName = rootObj[App::kStrPointTableDlt645CustomName].toString();
    }
    // 点表
    if (rootObj.contains(App::kStrPointTableDlt645Point) && rootObj[App::kStrPointTableDlt645Point].isArray()) {
        QJsonArray pointsArray = rootObj[App::kStrPointTableDlt645Point].toArray();
        pointTab.points = ParseDlt645PointArray(pointsArray);
    }

    return pointTab;
}

QList<Dlt645PointStruct::Point_T> JsonParse::ParseDlt645PointArray(const QJsonArray &pointsArray)
{
    QList<Dlt645PointStruct::Point_T> list;
    for (int i = 0; i < pointsArray.size(); ++i) {
        QJsonValue value = pointsArray.at(i); // 获取第 i 个元素
        if(value.isArray() != true) {
            continue;
        }
        QJsonArray pointArray = value.toArray();
        // 判断数组大小
        if(pointArray.size() != App::kDlt645TabColumns) {
            continue;
        }
        // 定义一个点结构
        Dlt645PointStruct::Point_T mps;
        // 起始地址
        QJsonValue jsonDataIdent = pointArray.at(App::kDlt645TabColumnId_DataIdent);
        if(jsonDataIdent.isString()) {
            mps.dataIdent = jsonDataIdent.toString();
        }
        // 读取周期
        QJsonValue jsonReadCycle = pointArray.at(App::kDlt645TabColumnId_ReadCycle);
        if(jsonReadCycle.isDouble()) {    // Qt5.9及以下只有isDouble，没有isInt
            mps.readCycle = jsonReadCycle.toInt();
        }
        // 名称
        QJsonValue jsonName = pointArray.at(App::kDlt645TabColumnId_Name);
        if(jsonName.isString()) {
            mps.customName = jsonName.toString();
        }
        // 将点结构记录到list中
        list.append(mps);
    }

    return list;
}

// 解析ModbusRtu通讯通道文件
QMap<QString, ModbusRtuChStruct::Ch_T> JsonParse::ParseModbusRtuChs(const QString &fileName)
{
    QJsonObject rootObj = JsonFile2JsonObj(fileName);
    if(rootObj.isEmpty()) {
        return QMap<QString, ModbusRtuChStruct::Ch_T>();
    }

    QMap<QString, ModbusRtuChStruct::Ch_T> map_ch;
    // 通道
    if (rootObj.contains(App::kStrChModbusRtuChannel) && rootObj[App::kStrChModbusRtuChannel].isArray()) {
        QJsonArray chArray = rootObj[App::kStrChModbusRtuChannel].toArray();
        for (int i = 0; i < chArray.size(); ++i) {
            QJsonValue chValue = chArray.at(i); // 获取第 i 个元素
            if(chValue.isObject() != true) {
                continue;
            }
            ModbusRtuChStruct::Ch_T ch = ParseModbusRtuCh(chValue.toObject());
            map_ch.insert(ch.name, ch);
        }
    }
    return map_ch;
}
ModbusRtuChStruct::Ch_T JsonParse::ParseModbusRtuCh(const QJsonObject &chObj)
{
    ModbusRtuChStruct::Ch_T ch;
    // 名称
    if(chObj.contains(App::kStrChModbusRtuName) && chObj[App::kStrChModbusRtuName].isString()) {
        ch.name = chObj[App::kStrChModbusRtuName].toString();
    }
    // 自定义名称
    if(chObj.contains(App::kStrChModbusRtuCustomName) && chObj[App::kStrChModbusRtuCustomName].isString()) {
        ch.customName = chObj[App::kStrChModbusRtuCustomName].toString();
    }
    // 接口
    if(chObj.contains(App::kStrChModbusRtuInterface) && chObj[App::kStrChModbusRtuInterface].isString()) {
        ch.interface = chObj[App::kStrChModbusRtuInterface].toString();
    }
    // 波特率
    if(chObj.contains(App::kStrChModbusRtuBaudRate) && chObj[App::kStrChModbusRtuBaudRate].isString()) {
        ch.baudRate = chObj[App::kStrChModbusRtuBaudRate].toString();
    }
    // 数据位
    if(chObj.contains(App::kStrChModbusRtuDataBits) && chObj[App::kStrChModbusRtuDataBits].isString()) {
        ch.dataBits = chObj[App::kStrChModbusRtuDataBits].toString();
    }
    // 停止位
    if(chObj.contains(App::kStrChModbusRtuStopBits) && chObj[App::kStrChModbusRtuStopBits].isString()) {
        ch.stopBits = chObj[App::kStrChModbusRtuStopBits].toString();
    }
    // 校验位
    if(chObj.contains(App::kStrChModbusRtuParity) && chObj[App::kStrChModbusRtuParity].isString()) {
        ch.parity = chObj[App::kStrChModbusRtuParity].toString();
    }
    return ch;
}

// 解析ModbusTcp通讯通道文件
QMap<QString, ModbusTcpChStruct::Ch_T> JsonParse::ParseModbusTcpChs(const QString &fileName)
{
    QJsonObject rootObj = JsonFile2JsonObj(fileName);
    if(rootObj.isEmpty()) {
        return QMap<QString, ModbusTcpChStruct::Ch_T>();
    }

    QMap<QString, ModbusTcpChStruct::Ch_T> map_ch;
    // 通道
    if (rootObj.contains(App::kStrChModbusTcpChannel) && rootObj[App::kStrChModbusTcpChannel].isArray()) {
        QJsonArray chArray = rootObj[App::kStrChModbusTcpChannel].toArray();
        for (int i = 0; i < chArray.size(); ++i) {
            QJsonValue chValue = chArray.at(i); // 获取第 i 个元素
            if(chValue.isObject() != true) {
                continue;
            }
            ModbusTcpChStruct::Ch_T ch = ParseModbusTcpCh(chValue.toObject());
            map_ch.insert(ch.name, ch);
        }
    }
    return map_ch;
}
ModbusTcpChStruct::Ch_T JsonParse::ParseModbusTcpCh(const QJsonObject &chObj)
{
    ModbusTcpChStruct::Ch_T ch;
    // 名称
    if(chObj.contains(App::kStrChModbusTcpName) && chObj[App::kStrChModbusTcpName].isString()) {
        ch.name = chObj[App::kStrChModbusTcpName].toString();
    }
    // 自定义名称
    if(chObj.contains(App::kStrChModbusTcpCustomName) && chObj[App::kStrChModbusTcpCustomName].isString()) {
        ch.customName = chObj[App::kStrChModbusTcpCustomName].toString();
    }
    // IP
    if(chObj.contains(App::kStrChModbusTcpIp) && chObj[App::kStrChModbusTcpIp].isString()) {
        ch.ip = chObj[App::kStrChModbusTcpIp].toString();
    }
    // 端口
    if(chObj.contains(App::kStrChModbusTcpPort) && chObj[App::kStrChModbusTcpPort].isDouble()) {
        ch.port = chObj[App::kStrChModbusTcpPort].toInt();
    }
    return ch;
}

// 解析Dlt645通讯通道文件
QMap<QString, Dlt645ChStruct::Ch_T> JsonParse::ParseDlt645Chs(const QString &fileName)
{
    QJsonObject rootObj = JsonFile2JsonObj(fileName);
    if(rootObj.isEmpty()) {
        return QMap<QString, Dlt645ChStruct::Ch_T>();
    }

    QMap<QString, Dlt645ChStruct::Ch_T> map_ch;
    // 通道
    if (rootObj.contains(App::kStrChDlt645Channel) && rootObj[App::kStrChDlt645Channel].isArray()) {
        QJsonArray chArray = rootObj[App::kStrChDlt645Channel].toArray();
        for (int i = 0; i < chArray.size(); ++i) {
            QJsonValue chValue = chArray.at(i); // 获取第 i 个元素
            if(chValue.isObject() != true) {
                continue;
            }
            Dlt645ChStruct::Ch_T ch = ParseDlt645Ch(chValue.toObject());
            map_ch.insert(ch.name, ch);
        }
    }
    return map_ch;
}
Dlt645ChStruct::Ch_T JsonParse::ParseDlt645Ch(const QJsonObject &chObj)
{
    Dlt645ChStruct::Ch_T ch;
    // 名称
    if(chObj.contains(App::kStrChDlt645Name) && chObj[App::kStrChDlt645Name].isString()) {
        ch.name = chObj[App::kStrChDlt645Name].toString();
    }
    // 自定义名称
    if(chObj.contains(App::kStrChDlt645CustomName) && chObj[App::kStrChDlt645CustomName].isString()) {
        ch.customName = chObj[App::kStrChDlt645CustomName].toString();
    }
    // 接口
    if(chObj.contains(App::kStrChDlt645Interface) && chObj[App::kStrChDlt645Interface].isString()) {
        ch.interface = chObj[App::kStrChDlt645Interface].toString();
    }
    // 波特率
    if(chObj.contains(App::kStrChDlt645BaudRate) && chObj[App::kStrChDlt645BaudRate].isString()) {
        ch.baudRate = chObj[App::kStrChDlt645BaudRate].toString();
    }
    // 数据位
    if(chObj.contains(App::kStrChDlt645DataBits) && chObj[App::kStrChDlt645DataBits].isString()) {
        ch.dataBits = chObj[App::kStrChDlt645DataBits].toString();
    }
    // 停止位
    if(chObj.contains(App::kStrChDlt645StopBits) && chObj[App::kStrChDlt645StopBits].isString()) {
        ch.stopBits = chObj[App::kStrChDlt645StopBits].toString();
    }
    // 校验位
    if(chObj.contains(App::kStrChDlt645Parity) && chObj[App::kStrChDlt645Parity].isString()) {
        ch.parity = chObj[App::kStrChDlt645Parity].toString();
    }
    return ch;
}

// 解析ModbusRtu通讯设备文件
QMap<QString, ModbusRtuDevStruct::Dev_T> JsonParse::ParseModbusRtuDevs(const QString &fileName)
{
    QJsonObject rootObj = JsonFile2JsonObj(fileName);
    if(rootObj.isEmpty()) {
        return QMap<QString, ModbusRtuDevStruct::Dev_T>();
    }

    QMap<QString, ModbusRtuDevStruct::Dev_T> map_dev;
    // 设备
    if(rootObj.contains(App::kStrDevModbusRtuDevice) && rootObj[App::kStrDevModbusRtuDevice].isArray()) {
        QJsonArray devArray = rootObj[App::kStrDevModbusRtuDevice].toArray();
        for(int i = 0; i < devArray.size(); ++i) {
            QJsonValue devValue = devArray.at(i); // 获取第 i 个元素
            if(devValue.isObject() != true) {
                continue;
            }
            ModbusRtuDevStruct::Dev_T dev = ParseModbusRtuDev(devValue.toObject());
            map_dev.insert(dev.name, dev);
        }
    }
    return map_dev;
}
ModbusRtuDevStruct::Dev_T JsonParse::ParseModbusRtuDev(const QJsonObject &chObj)
{
    ModbusRtuDevStruct::Dev_T dev;
    // 名称
    if(chObj.contains(App::kStrDevModbusRtuName) && chObj[App::kStrDevModbusRtuName].isString()) {
        dev.name = chObj[App::kStrDevModbusRtuName].toString();
    }
    // 自定义名称
    if(chObj.contains(App::kStrDevModbusRtuCustomName) && chObj[App::kStrDevModbusRtuCustomName].isString()) {
        dev.customName = chObj[App::kStrDevModbusRtuCustomName].toString();
    }
    // 所处通讯通道的工程名
    if(chObj.contains(App::kStrDevModbusRtuChannel) && chObj[App::kStrDevModbusRtuChannel].isString()) {
        dev.channelPrjName = chObj[App::kStrDevModbusRtuChannel].toString();
    }
    // 所使用点表的工程名
    if(chObj.contains(App::kStrDevModbusRtuPointTable) && chObj[App::kStrDevModbusRtuPointTable].isString()) {
        dev.pointTablePrjName = chObj[App::kStrDevModbusRtuPointTable].toString();
    }
    // 地址
    if(chObj.contains(App::kStrDevModbusRtuAddress) && chObj[App::kStrDevModbusRtuAddress].isString()) {
        dev.address = chObj[App::kStrDevModbusRtuAddress].toString();
    }
    return dev;
}

// 解析ModbusTcp通讯设备文件
QMap<QString, ModbusTcpDevStruct::Dev_T> JsonParse::ParseModbusTcpDevs(const QString &fileName)
{
    QJsonObject rootObj = JsonFile2JsonObj(fileName);
    if(rootObj.isEmpty()) {
        return QMap<QString, ModbusTcpDevStruct::Dev_T>();
    }

    QMap<QString, ModbusTcpDevStruct::Dev_T> map_dev;
    // 设备
    if(rootObj.contains(App::kStrDevModbusTcpDevice) && rootObj[App::kStrDevModbusTcpDevice].isArray()) {
        QJsonArray devArray = rootObj[App::kStrDevModbusTcpDevice].toArray();
        for(int i = 0; i < devArray.size(); ++i) {
            QJsonValue devValue = devArray.at(i); // 获取第 i 个元素
            if(devValue.isObject() != true) {
                continue;
            }
            ModbusTcpDevStruct::Dev_T dev = ParseModbusTcpDev(devValue.toObject());
            map_dev.insert(dev.name, dev);
        }
    }
    return map_dev;
}
ModbusTcpDevStruct::Dev_T JsonParse::ParseModbusTcpDev(const QJsonObject &chObj)
{
    ModbusTcpDevStruct::Dev_T dev;
    // 名称
    if(chObj.contains(App::kStrDevModbusTcpName) && chObj[App::kStrDevModbusTcpName].isString()) {
        dev.name = chObj[App::kStrDevModbusTcpName].toString();
    }
    // 自定义名称
    if(chObj.contains(App::kStrDevModbusTcpCustomName) && chObj[App::kStrDevModbusTcpCustomName].isString()) {
        dev.customName = chObj[App::kStrDevModbusTcpCustomName].toString();
    }
    // 所处通讯通道的工程名
    if(chObj.contains(App::kStrDevModbusTcpChannel) && chObj[App::kStrDevModbusTcpChannel].isString()) {
        dev.channelPrjName = chObj[App::kStrDevModbusTcpChannel].toString();
    }
    // 所使用点表的工程名
    if(chObj.contains(App::kStrDevModbusTcpPointTable) && chObj[App::kStrDevModbusTcpPointTable].isString()) {
        dev.pointTablePrjName = chObj[App::kStrDevModbusTcpPointTable].toString();
    }
    // 地址
    if(chObj.contains(App::kStrDevModbusTcpAddress) && chObj[App::kStrDevModbusTcpAddress].isString()) {
        dev.address = chObj[App::kStrDevModbusTcpAddress].toString();
    }
    return dev;
}

// 解析Dlt645通讯设备文件
QMap<QString, Dlt645DevStruct::Dev_T> JsonParse::ParseDlt645Devs(const QString &fileName)
{
    QJsonObject rootObj = JsonFile2JsonObj(fileName);
    if(rootObj.isEmpty()) {
        return QMap<QString, Dlt645DevStruct::Dev_T>();
    }

    QMap<QString, Dlt645DevStruct::Dev_T> map_dev;
    // 设备
    if(rootObj.contains(App::kStrDevDlt645Device) && rootObj[App::kStrDevDlt645Device].isArray()) {
        QJsonArray devArray = rootObj[App::kStrDevDlt645Device].toArray();
        for(int i = 0; i < devArray.size(); ++i) {
            QJsonValue devValue = devArray.at(i); // 获取第 i 个元素
            if(devValue.isObject() != true) {
                continue;
            }
            Dlt645DevStruct::Dev_T dev = ParseDlt645Dev(devValue.toObject());
            map_dev.insert(dev.name, dev);
        }
    }
    return map_dev;
}
Dlt645DevStruct::Dev_T JsonParse::ParseDlt645Dev(const QJsonObject &chObj)
{
    Dlt645DevStruct::Dev_T dev;
    // 名称
    if(chObj.contains(App::kStrDevDlt645Name) && chObj[App::kStrDevDlt645Name].isString()) {
        dev.name = chObj[App::kStrDevDlt645Name].toString();
    }
    // 自定义名称
    if(chObj.contains(App::kStrDevDlt645CustomName) && chObj[App::kStrDevDlt645CustomName].isString()) {
        dev.customName = chObj[App::kStrDevDlt645CustomName].toString();
    }
    // 所处通讯通道的工程名
    if(chObj.contains(App::kStrDevDlt645Channel) && chObj[App::kStrDevDlt645Channel].isString()) {
        dev.channelPrjName = chObj[App::kStrDevDlt645Channel].toString();
    }
    // 所使用点表的工程名
    if(chObj.contains(App::kStrDevDlt645PointTable) && chObj[App::kStrDevDlt645PointTable].isString()) {
        dev.pointTablePrjName = chObj[App::kStrDevDlt645PointTable].toString();
    }
    // 地址
    if(chObj.contains(App::kStrDevDlt645Address) && chObj[App::kStrDevDlt645Address].isString()) {
        dev.address = chObj[App::kStrDevDlt645Address].toString();
    }
    return dev;
}
