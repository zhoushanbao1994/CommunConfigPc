#ifndef DLT645POINTSTRUCT_H
#define DLT645POINTSTRUCT_H
#include <QString>
#include <QList>

class Dlt645PointStruct
{
public:
    explicit Dlt645PointStruct();

    typedef struct Point_ {
        QString dataIdent = "0x00000000";   // 数据标识
        int readCycle = 1000;               // 读取周期ms
        QString customName = "";            // 自定义名称
    } Point_T;
    typedef struct PointTab_ {
        QString fileName = "";              // 文件名
        QString name = "";                  // 名称
        QList<Point_T> points;              // 点结构
    } PointTab_T;
};

#endif // DLT645POINTSTRUCT_H
