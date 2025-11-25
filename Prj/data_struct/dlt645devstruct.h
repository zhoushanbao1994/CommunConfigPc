#ifndef DLT645DEVSTRUCT_H
#define DLT645DEVSTRUCT_H
#include <QString>
#include <QList>

class Dlt645DevStruct
{
public:
    explicit Dlt645DevStruct();

    typedef struct Dev_ {
        QString name = "";          // 名称
        QString channel = "";       // 所在通道
        QString pointTable = "";    // 所使用的点表
        QString address = "1";      // 地址
    } Dev_T;
};

#endif // DLT645DEVSTRUCT_H
