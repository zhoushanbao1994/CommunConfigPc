#ifndef MODBUSTCPCHSTRUCT_H
#define MODBUSTCPCHSTRUCT_H
#include <QString>
#include <QList>

class ModbusTcpChStruct
{
public:
    explicit ModbusTcpChStruct();

    typedef struct Ch_ {
        QString name = "";              // 名称
        QString ip = "192.168.123.123"; // IP
        quint16 port  = 502;            // 端口
    } Ch_T;
    //typedef struct Chs_ {
    //    QString fileName = "";          // 文件名
    //    QString name = "";              // 名称
    //    QList<Ch_T> chs;                // 点结构
    //} Chs_T;
};

#endif // MODBUSTCPCHSTRUCT_H
