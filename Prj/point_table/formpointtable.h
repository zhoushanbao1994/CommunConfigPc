#ifndef FORMPOINTTABLE_H
#define FORMPOINTTABLE_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "customtablewidget.h"
#include "app.h"

namespace Ui {
class FormPointTable;
}

class FormPointTable : public QWidget
{
    Q_OBJECT

private:
    // Modbus表格的总列数
    const int kModbusTabColumns             = 6;
    // 每个数据类型的列号(位于表格中的哪一列)
    const int kModbusTabColumnId_StartAddr  = 0;    // 起始地址
    const int kModbusTabColumnId_PointNum   = 1;    // 点数量
    const int kModbusTabColumnId_Code       = 2;    // 功能码
    const int kModbusTabColumnId_DataType   = 3;    // 数据类型
    const int kModbusTabColumnId_ReadCycle  = 4;    // 读取周期
    const int kModbusTabColumnId_Name       = 5;    // 名称

    // Dlt645表格的总列数
    const int kDlt645TabColumns             = 3;
    // 每个数据类型的列号(位于表格中的哪一列)
    const int kDlt645TabColumnId_DataIdent  = 0;    // 数据标识
    const int kDlt645TabColumnId_ReadCycle  = 1;    // 点数量
    const int kDlt645TabColumnId_Name       = 2;    // 功能码

public:
    explicit FormPointTable(
        App::PointTabType_E type, QTreeWidgetItem *item, QString &prj_name,
        QWidget *parent = nullptr);
    ~FormPointTable();

private slots:
    void on_comboBox_Type_currentTextChanged(const QString &arg1);

    void PrjNameTextEdited_Slot(const QString &text);
    void CustomNameTextEdited_Slot(const QString &text);

private:
    // 表格主体初始化
    void TableWidget_Init();
    // 填充一行数据
    void ModbusTableWidget_RowSet(
        int row, quint16 start_addr, quint16 point_num, const QString &code,
        const QString &data_type, int read_cycle, const QString &name);
    // 填充一行数据
    void Dlt645TableWidget_RowSet(
        int row, const QString &code, int read_cycle, const QString &name);

private:
    Ui::FormPointTable *ui;
    App::PointTabType_E type_;
    QTreeWidgetItem *item_ = nullptr;
    CustomTableWidget *modbus_tab_ = nullptr;
    CustomTableWidget *dlt645_tab_ = nullptr;
};

#endif // FORMPOINTTABLE_H
