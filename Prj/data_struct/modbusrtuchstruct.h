#ifndef MODBUSRTUCHSTRUCT_H
#define MODBUSRTUCHSTRUCT_H
#include <QString>
#include <QList>

class ModbusRtuChStruct
{
public:
    explicit ModbusRtuChStruct();

    typedef struct Ch_ {
        QString name = "";              // 名称
        QString customName = "";        // 自定义名称
        QString interface = "RS485_1";  // 接口
        QString baudRate = "9600";      // 波特率
        QString dataBits = "8";         // 数据位
        QString parity = "None";        // 校验位
        QString stopBits = "1";         // 停止位
    } Ch_T;
    //typedef struct Chs_ {
    //    QString fileName = "";          // 文件名
    //    QString name = "";              // 名称
    //    QList<Ch_T> chs;                // 通道
    //} Chs_T;
};

#endif // MODBUSRTUCHSTRUCT_H
