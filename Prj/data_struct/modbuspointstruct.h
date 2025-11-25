#ifndef MODBUSPOINTSTRUCT_H
#define MODBUSPOINTSTRUCT_H
#include <QString>
#include <QList>

class ModbusPointStruct
{
public:
    explicit ModbusPointStruct();

    typedef struct Point_ {
        quint16 startAddr = 0x0000;     // 起始地址
        quint16 pointNum = 0x0001;      // 点数量
        QString code = "0x03";          // 功能码
        QString dataType = "U16";       // 数据类型
        int readCycle = 1000;           // 读取周期ms
        QString customName = "";        // 自定义名称
    } Point_T;
    typedef struct PointTab_ {
        QString fileName = "";          // 文件名
        QString name = "";              // 名称
        QList<Point_T> points;          // 点结构
    } PointTab_T;
};

#endif // MODBUSPOINTSTRUCT_H
