#include "jsongenerat.h"
#include <QJsonObject>   // JSON 对象
#include <QJsonArray>    // JSON 数组
#include <QJsonDocument> // JSON 文档（序列化/反序列化）
#include <QFile>         // 文件操作（读写 JSON 文件）
#include <QMessageBox>
#include "app.h"

JsonGenerate::JsonGenerate(
        const QString &folder,
        QMap<QString, ModbusPointStruct::PointTab_T> &mpts, // Modbus点表
        QMap<QString, Dlt645PointStruct::PointTab_T> &dpts, // DLT645点表
        QMap<QString, ModbusRtuChStruct::Ch_T> &mrcs,       // ModbusRtu通道
        QMap<QString, ModbusTcpChStruct::Ch_T> &mtcs,       // ModbusTcp通道
        QMap<QString, Dlt645ChStruct::Ch_T> &dlcs,          // DLT645通道
        QMap<QString, ModbusRtuDevStruct::Dev_T> &mrds,     // ModbusRtu设备
        QMap<QString, ModbusTcpDevStruct::Dev_T> &mtds,     // ModbusTcp设备
        QMap<QString, Dlt645DevStruct::Dev_T> &dlds,        // DLT645设备
        bool debug,
        QObject *parent)
    : QObject{parent}
    , folder_(folder)           // 文件夹
    , dir_(QDir(folder_))
    , modbusPointTabs_(mpts)    // Modbus点表
    , dlt645PointTabs_(dpts)    // DLT645点表
    , modbusRtuChs_(mrcs)       // ModbusRtu通道
    , modbusTcpChs_(mtcs)       // ModbusTcp通道
    , dlt645Chs_(dlcs)          // DLT645通道
    , modbusRtuDevs_(mrds)      // ModbusRtu设备
    , modbusTcpDevs_(mtds)      // ModbusTcp设备
    , dlt645Devs_(dlds)         // DLT645设备
{
    QJsonDocument::JsonFormat forma = QJsonDocument::Indented;  // 格式化（易读）
    //QJsonDocument::JsonFormat forma = QJsonDocument::Compact;   // 紧凑（节省空间）

    // 生成点表
    modbusPointTabFileNames_.clear();                // Modbus点表文件名
    QMap<QString, ModbusPointStruct::PointTab_T>::const_iterator modbusPointTab;
    for(modbusPointTab = modbusPointTabs_.cbegin(); modbusPointTab != modbusPointTabs_.cend(); ++modbusPointTab) {
        QString key = modbusPointTab.key();
        QString file = GenerateModbusPoint(modbusPointTab.value(), forma, debug);
        modbusPointTabFileNames_.insert(key, file);
    }
    dlt645PointTabFileNames_.clear();                // DLT645点表文件名
    QMap<QString, Dlt645PointStruct::PointTab_T>::const_iterator dltPointTab;
    for(dltPointTab = dlt645PointTabs_.cbegin(); dltPointTab != dlt645PointTabs_.cend(); ++dltPointTab) {
        QString key = dltPointTab.key();
        QString file = GenerateDlt645Point(dltPointTab.value(), forma, debug);
        dlt645PointTabFileNames_.insert(key, file);
    }

    // 生成通道
    modbusRtuChFileName_ = GenerateModbusRtuChs(modbusRtuChs_, forma, debug);
    modbusTcpChFileName_ = GenerateModbusTcpChs(modbusTcpChs_, forma, debug);
    dlt645ChFileName_    = GenerateDlt645Chs(dlt645Chs_, forma, debug);

    // 生成设备
    modbusRtuDevFileName_ = GenerateModbusRtuDevs(modbusRtuDevs_, forma, debug);
    modbusTcpDevFileName_ = GenerateModbusTcpDevs(modbusTcpDevs_, forma, debug);
    dlt645DevFileName_    = GenerateDlt645Devs(dlt645Devs_, forma, debug);

    // 生成Index文件
    GenerateIndex(forma, debug);

    // 导出成功提示框（父窗口、标题、内容、按钮）
    QMessageBox::information(nullptr,
                             "导出成功",
                             "数据已成功导出到指定路径:\n" + folder,
                             QMessageBox::Ok);
}

// 生成Modbus点表文件
QString JsonGenerate::GenerateModbusPoint(const ModbusPointStruct::PointTab_T &pointTab,
                                          QJsonDocument::JsonFormat forma, bool debug)
{
    // 创建 JSON 对象
    QJsonObject rootObj;
    // 添加点表工程名
    rootObj.insert(App::kStrPointTableModbusName, pointTab.name);
    // 添加点表自定义名
    rootObj.insert(App::kStrPointTableModbusCustomName, pointTab.customName);
    // 添加点表点内容
    QJsonArray json_array = GenerateModbusPointArray(pointTab.points);
    rootObj.insert(App::kStrPointTableModbusPoint, json_array);
    // 保存文件
    QString fileName = (pointTab.fileName.isEmpty() == false) ?
                           pointTab.fileName :
                           (kStrPointTabFileNamePrefixModbus + pointTab.name + kStrFileFormat);
    JsonOjbSaveFile(rootObj, fileName, forma, debug);

    return fileName;
}

QJsonArray JsonGenerate::GenerateModbusPointArray(const QList<ModbusPointStruct::Point_T> &points)
{
    // 创建所有点的 JSON 数组
    QJsonArray pointsArray;

    for(const auto &point : points) {
        // 创建单点的 JSON 数组
        QJsonArray pointArray;
        // 起始地址
        pointArray.append(QString("0x%1").arg(point.startAddr, 4, 16, QChar('0')));
        // 点位数量
        pointArray.append(QString("0x%1").arg(point.pointNum, 4, 16, QChar('0')));
        // 功能码
        pointArray.append(point.code);
        // 数据类型
        pointArray.append(point.dataType);
        // 读取周期ms
        pointArray.append(point.readCycle);
        // 名称
        pointArray.append(point.customName);
        // 将单点添加到总数组中
        pointsArray.append(pointArray);
    }

    return pointsArray;
}

// 生成DLT645点表文件
QString JsonGenerate::GenerateDlt645Point(const Dlt645PointStruct::PointTab_T &pointTab,
                                          QJsonDocument::JsonFormat forma, bool debug)
{
    // 创建 JSON 对象
    QJsonObject rootObj;
    // 添加点表工程名
    rootObj.insert(App::kStrPointTableDlt645Name, pointTab.name);
    // 添加点表自定义名
    rootObj.insert(App::kStrPointTableDlt645CustomName, pointTab.customName);
    // 添加点表点内容
    QJsonArray json_array = GenerateDlt645PointArray(pointTab.points);
    rootObj.insert(App::kStrPointTableDlt645Point, json_array);
    // 保存文件
    QString fileName = (pointTab.fileName.isEmpty() == false) ?
                           pointTab.fileName :
                           (kStrPointTabFileNamePrefixDlt645 + pointTab.name + kStrFileFormat);
    JsonOjbSaveFile(rootObj, fileName, forma, debug);

    return fileName;
}
QJsonArray JsonGenerate::GenerateDlt645PointArray(const QList<Dlt645PointStruct::Point_T> &points)
{
    // 创建所有点的 JSON 数组
    QJsonArray pointsArray;

    for(const auto &point : points) {
        // 创建单点的 JSON 数组
        QJsonArray pointArray;
        // 起始数据标识
        pointArray.append(point.dataIdent);
        // 读取周期ms
        pointArray.append(point.readCycle);
        // 名称
        pointArray.append(point.customName);
        // 将单点添加到总数组中
        pointsArray.append(pointArray);
    }

    return pointsArray;
}

// 生成ModbusRtu通讯通道文件
QString JsonGenerate::GenerateModbusRtuChs(const QMap<QString, ModbusRtuChStruct::Ch_T> &chs,
                                           QJsonDocument::JsonFormat forma, bool debug)
{
    // 创建 JSON 数组
    QJsonArray chsArray;
    // 遍历每一个通道
    QMap<QString, ModbusRtuChStruct::Ch_T>::const_iterator it;
    for (it = chs.cbegin(); it != chs.cend(); ++it) {
        ModbusRtuChStruct::Ch_T ch = it.value();
        // 生成单个通道的信息
        QJsonObject chObj = GenerateModbusRtuCh(ch);
        // 添加通道
        chsArray.append(chObj);
    }
    // 创建 JSON 对象
    QJsonObject rootObj;
    // 添加通道
    rootObj.insert(App::kStrChModbusTcpChannel, chsArray);
    // 保存文件
    QString fileName = kStrCommunChFileNameModbusRtu + kStrFileFormat;
    JsonOjbSaveFile(rootObj, fileName, forma, debug);

    return fileName;
}
QJsonObject JsonGenerate::GenerateModbusRtuCh(const ModbusRtuChStruct::Ch_T &ch)
{
    QJsonObject chObj;
    // 通道名称
    chObj.insert(App::kStrChModbusRtuName, ch.name);
    // 自定义名称
    chObj.insert(App::kStrChModbusRtuCustomName, ch.customName);
    // 接口
    chObj.insert(App::kStrChModbusRtuInterface, ch.interface);
    // 波特率
    chObj.insert(App::kStrChModbusRtuBaudRate, ch.baudRate);
    // 数据位
    chObj.insert(App::kStrChModbusRtuDataBits, ch.dataBits);
    // 停止位
    chObj.insert(App::kStrChModbusRtuStopBits, ch.stopBits);
    // 校验位
    chObj.insert(App::kStrChModbusRtuParity, ch.parity);

    return chObj;
}

// 生成ModbusTcp通讯通道文件
QString JsonGenerate::GenerateModbusTcpChs(const QMap<QString, ModbusTcpChStruct::Ch_T> &chs,
                                           QJsonDocument::JsonFormat forma, bool debug)
{
    // 创建 JSON 数组
    QJsonArray chsArray;
    // 遍历每一个通道
    QMap<QString, ModbusTcpChStruct::Ch_T>::const_iterator it;
    for (it = chs.cbegin(); it != chs.cend(); ++it) {
        ModbusTcpChStruct::Ch_T ch = it.value();
        // 生成单个通道的信息
        QJsonObject chObj = GenerateModbusTcpCh(ch);
        // 添加通道
        chsArray.append(chObj);
    }
    // 创建 JSON 对象
    QJsonObject rootObj;
    // 添加通道
    rootObj.insert(App::kStrChModbusTcpChannel, chsArray);
    // 保存文件
    QString fileName = kStrCommunChFileNameModbusTcp + kStrFileFormat;
    JsonOjbSaveFile(rootObj, fileName, forma, debug);

    return fileName;
}
QJsonObject JsonGenerate::GenerateModbusTcpCh(const ModbusTcpChStruct::Ch_T &ch)
{
    QJsonObject chObj;
    // 通道名称
    chObj.insert(App::kStrChModbusTcpName, ch.name);
    // 自定义名称
    chObj.insert(App::kStrChModbusTcpCustomName, ch.customName);
    // IP
    chObj.insert(App::kStrChModbusTcpIp, ch.ip);
    // 端口
    chObj.insert(App::kStrChModbusTcpPort, ch.port);

    return chObj;
}

// 生成Dlt645通讯通道文件
QString JsonGenerate::GenerateDlt645Chs(const QMap<QString, Dlt645ChStruct::Ch_T> &chs,
                                        QJsonDocument::JsonFormat forma, bool debug)
{
    // 创建 JSON 数组
    QJsonArray chsArray;
    // 遍历每一个通道
    QMap<QString, Dlt645ChStruct::Ch_T>::const_iterator it;
    for (it = chs.cbegin(); it != chs.cend(); ++it) {
        Dlt645ChStruct::Ch_T ch = it.value();
        // 生成单个通道的信息
        QJsonObject chObj = GenerateDlt645Ch(ch);
        // 添加通道
        chsArray.append(chObj);
    }
    // 创建 JSON 对象
    QJsonObject rootObj;
    // 添加通道
    rootObj.insert(App::kStrChDlt645Channel, chsArray);
    // 保存文件
    QString fileName = kStrCommunChFileNameDlt645 + kStrFileFormat;
    JsonOjbSaveFile(rootObj, fileName, forma, debug);

    return fileName;
}
QJsonObject JsonGenerate::GenerateDlt645Ch(const Dlt645ChStruct::Ch_T &ch)
{
    QJsonObject chObj;
    // 通道名称
    chObj.insert(App::kStrChDlt645Name, ch.name);
    // 自定义名称
    chObj.insert(App::kStrChDlt645CustomName, ch.customName);
    // 接口
    chObj.insert(App::kStrChDlt645Interface, ch.interface);
    // 波特率
    chObj.insert(App::kStrChDlt645BaudRate, ch.baudRate);
    // 数据位
    chObj.insert(App::kStrChDlt645DataBits, ch.dataBits);
    // 停止位
    chObj.insert(App::kStrChDlt645StopBits, ch.stopBits);
    // 校验位
    chObj.insert(App::kStrChDlt645Parity, ch.parity);

    return chObj;
}

// 生成ModbusRtu通讯设备文件
QString JsonGenerate::GenerateModbusRtuDevs(const QMap<QString, ModbusRtuDevStruct::Dev_T> &devs,
                                            QJsonDocument::JsonFormat forma, bool debug)
{
    // 创建 JSON 数组
    QJsonArray devsArray;
    // 遍历每一个设备
    QMap<QString, ModbusRtuDevStruct::Dev_T>::const_iterator it;
    for (it = devs.cbegin(); it != devs.cend(); ++it) {
        ModbusRtuDevStruct::Dev_T dev = it.value();
        // 生成单个设备的信息
        QJsonObject devObj = GenerateModbusRtuDev(dev);
        // 添加设备
        devsArray.append(devObj);
    }
    // 创建 JSON 对象
    QJsonObject rootObj;
    // 添加设备
    rootObj.insert(App::kStrDevModbusRtuDevice, devsArray);
    // 保存文件
    QString fileName = kStrCommunDevFileNameModbusRtu + kStrFileFormat;
    JsonOjbSaveFile(rootObj, fileName, forma, debug);

    return fileName;
}
QJsonObject JsonGenerate::GenerateModbusRtuDev(const ModbusRtuDevStruct::Dev_T &dev)
{
    QJsonObject devObj;
    // 设备名称
    devObj.insert(App::kStrDevModbusRtuName, dev.name);
    // 自定义名称
    devObj.insert(App::kStrDevModbusRtuCustomName, dev.customName);
    // 所在通道的工程名
    devObj.insert(App::kStrDevModbusRtuChannel, dev.channelPrjName);
    // 所使用点表的工程名
    devObj.insert(App::kStrDevModbusRtuPointTable, dev.pointTablePrjName);
    // 地址
    devObj.insert(App::kStrDevModbusRtuAddress, dev.address);

    return devObj;
}

// 生成ModbusTcp通讯设备文件
QString JsonGenerate::GenerateModbusTcpDevs(const QMap<QString, ModbusTcpDevStruct::Dev_T> &devs,
                                            QJsonDocument::JsonFormat forma, bool debug)
{
    // 创建 JSON 数组
    QJsonArray devsArray;
    // 遍历每一个设备
    QMap<QString, ModbusTcpDevStruct::Dev_T>::const_iterator it;
    for (it = devs.cbegin(); it != devs.cend(); ++it) {
        ModbusTcpDevStruct::Dev_T dev = it.value();
        // 生成单个设备的信息
        QJsonObject devObj = GenerateModbusTcpDev(dev);
        // 添加设备
        devsArray.append(devObj);
    }
    // 创建 JSON 对象
    QJsonObject rootObj;
    // 添加设备
    rootObj.insert(App::kStrDevModbusTcpDevice, devsArray);
    // 保存文件
    QString fileName = kStrCommunDevFileNameModbusTcp + kStrFileFormat;
    JsonOjbSaveFile(rootObj, fileName, forma, debug);

    return fileName;
}
QJsonObject JsonGenerate::GenerateModbusTcpDev(const ModbusTcpDevStruct::Dev_T &dev)
{
    QJsonObject devObj;
    // 设备名称
    devObj.insert(App::kStrDevModbusTcpName, dev.name);
    // 自定义名称
    devObj.insert(App::kStrDevModbusTcpCustomName, dev.customName);
    // 所在通道的工程名
    devObj.insert(App::kStrDevModbusTcpChannel, dev.channelPrjName);
    // 所使用点表的工程名
    devObj.insert(App::kStrDevModbusTcpPointTable, dev.pointTablePrjName);
    // 地址
    devObj.insert(App::kStrDevModbusTcpAddress, dev.address);

    return devObj;
}

// 生成Dlt645通讯设备文件
QString JsonGenerate::GenerateDlt645Devs(const QMap<QString, Dlt645DevStruct::Dev_T> &devs,
                                         QJsonDocument::JsonFormat forma, bool debug)
{
    // 创建 JSON 数组
    QJsonArray devsArray;
    // 遍历每一个设备
    QMap<QString, Dlt645DevStruct::Dev_T>::const_iterator it;
    for (it = devs.cbegin(); it != devs.cend(); ++it) {
        Dlt645DevStruct::Dev_T dev = it.value();
        // 生成单个设备的信息
        QJsonObject devObj = GenerateDlt645Dev(dev);
        // 添加设备
        devsArray.append(devObj);
    }
    // 创建 JSON 对象
    QJsonObject rootObj;
    // 添加设备
    rootObj.insert(App::kStrDevDlt645Device, devsArray);
    // 保存文件
    QString fileName = kStrCommunDevFileNameDlt645 + kStrFileFormat;
    JsonOjbSaveFile(rootObj, fileName, forma, debug);

    return fileName;
}
QJsonObject JsonGenerate::GenerateDlt645Dev(const Dlt645DevStruct::Dev_T &dev)
{
    QJsonObject devObj;
    // 设备名称
    devObj.insert(App::kStrDevDlt645Name, dev.name);
    // 自定义名称
    devObj.insert(App::kStrDevDlt645CustomName, dev.customName);
    // 所在通道的工程名
    devObj.insert(App::kStrDevDlt645Channel, dev.channelPrjName);
    // 所使用点表的工程名
    devObj.insert(App::kStrDevDlt645PointTable, dev.pointTablePrjName);
    // 地址
    devObj.insert(App::kStrDevDlt645Address, dev.address);

    return devObj;
}

// 生成Index文件
QString JsonGenerate::GenerateIndex(QJsonDocument::JsonFormat forma,bool debug)
{
    QMap<QString, QString>::const_iterator it;
    // Modbus点表
    QJsonObject pointModbusObj;
    for(it = modbusPointTabFileNames_.cbegin(); it != modbusPointTabFileNames_.cend(); ++it) {
        pointModbusObj.insert(it.key(), it.value());
    }
    // DLT645点表
    QJsonObject pointDlt645Obj;
    for(it = dlt645PointTabFileNames_.cbegin(); it != dlt645PointTabFileNames_.cend(); ++it) {
        pointDlt645Obj.insert(it.key(), it.value());
    }
    // 点表
    QJsonObject pointObj;
    pointObj.insert(App::kStrPointTableTypeModbus, pointModbusObj);
    pointObj.insert(App::kStrPointTableTypeDlt645, pointDlt645Obj);

    // 通讯通道
    QJsonObject chObj;
    chObj.insert(App::kStrCommunChTypeModbusRtu, modbusRtuChFileName_);
    chObj.insert(App::kStrCommunChTypeModbusTcp, modbusTcpChFileName_);
    chObj.insert(App::kStrCommunChTypeDlt645   , dlt645ChFileName_   );
    // 通讯设备
    QJsonObject devObj;
    devObj.insert(App::kStrCommunDevTypeModbusRtu, modbusRtuDevFileName_);
    devObj.insert(App::kStrCommunDevTypeModbusTcp, modbusTcpDevFileName_);
    devObj.insert(App::kStrCommunDevTypeDlt645   , dlt645DevFileName_   );

    // 创建 JSON 对象
    QJsonObject rootObj;
    // 添加点表
    rootObj.insert(App::kStrPointTable, pointObj);
    // 添加通讯通道
    rootObj.insert(App::kStrCommunCh, chObj);
    // 添加通讯设备
    rootObj.insert(App::kStrCommunDev, devObj);
    // 名称
    rootObj.insert(App::kStrPrjName, "xxxx");

    // 保存文件
    QString fileName = kStrIndexFileName + kStrFileFormat;
    JsonOjbSaveFile(rootObj, fileName, forma, debug);

    return fileName;
}

// 将JSON写入到文件中保存
bool JsonGenerate::JsonOjbSaveFile(const QJsonObject obj, const QString fileName,
                     QJsonDocument::JsonFormat forma, bool debug)
{
    // 文件绝对路径
    QString fileAbsoluteName = dir_.filePath(fileName);
    // 打开文件
    QFile file(fileAbsoluteName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << fileAbsoluteName << "无法打开文件写入：" << file.errorString();
        return false;
    }

    // 生成 JSON 文档（JSON对象）
    QJsonDocument doc(obj);
    // 序列化为字符串（两种格式）
    QByteArray jsonStr = doc.toJson(forma); // QJsonDocument::Indented 格式化（易读）
        //                                     QJsonDocument::Compact  紧凑（节省空间）
    // 打印JSON信息
    if(debug) {
        qDebug() << "fileName:" << fileAbsoluteName << ", JSON:" << jsonStr;
    }

    file.write(jsonStr);
    file.close();
    qDebug() << "JSON 已写入文件：" << fileAbsoluteName;

    return true;
}
