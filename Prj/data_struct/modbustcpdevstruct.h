#ifndef MODBUSTCPDEVSTRUCT_H
#define MODBUSTCPDEVSTRUCT_H
#include <QString>
#include <QList>

class ModbusTcpDevStruct
{
public:
    explicit ModbusTcpDevStruct();

    typedef struct Dev_ {
        QString name = "";          // 名称
        QString channel = "";       // 所在通道
        QString pointTable = "";    // 所使用的点表
        QString address = "1";      // 地址
    } Dev_T;
};

#endif // MODBUSTCPDEVSTRUCT_H
