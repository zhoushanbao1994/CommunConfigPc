#ifndef DLT645DEVSTRUCT_H
#define DLT645DEVSTRUCT_H
#include <QString>
#include <QList>

class Dlt645DevStruct
{
public:
    explicit Dlt645DevStruct();

    typedef struct Dev_ {
        QString name = "";              // 名称
        QString customName = "";        // 自定义名称
        QString channelPrjName = "";    // 所在通道的工程名
        QString pointTablePrjName = ""; // 所使用点表的工程名
        QString address = "1";          // 地址
    } Dev_T;
};

#endif // DLT645DEVSTRUCT_H
