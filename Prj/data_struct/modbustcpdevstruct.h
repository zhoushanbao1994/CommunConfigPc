#ifndef MODBUSTCPDEVSTRUCT_H
#define MODBUSTCPDEVSTRUCT_H
#include <QString>
#include <QList>

class ModbusTcpDevStruct
{
public:
    explicit ModbusTcpDevStruct();

    typedef struct Dev_ {
        QString name = "";              // 名称
        QString customName = "";        // 自定义名称
        QString channelPrjName = "";    // 所在通道的工程名
        QString pointTablePrjName = ""; // 所使用点表的工程名
        QString address = "1";          // 地址
    } Dev_T;
};

#endif // MODBUSTCPDEVSTRUCT_H
