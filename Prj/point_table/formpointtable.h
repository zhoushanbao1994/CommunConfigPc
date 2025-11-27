#ifndef FORMPOINTTABLE_H
#define FORMPOINTTABLE_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "customtablewidget.h"
#include "app.h"
#include "data_struct/modbuspointstruct.h"
#include "data_struct/dlt645pointstruct.h"

namespace Ui {
class FormPointTable;
}

class FormPointTable : public QWidget
{
    Q_OBJECT
public:
    explicit FormPointTable(
        App::PointTabType_E type, QTreeWidgetItem *item, QString &prjName,
        QString &customName, QWidget *parent = nullptr);
    ~FormPointTable();
    // 填充一行数据
    void ModbusTableWidget_RowSet(
        int row, ModbusPointStruct::Point_T &point);
    // 填充一行数据
    void Dlt645TableWidget_RowSet(
        int row, Dlt645PointStruct::Point_T &point);

    // 获取页头参数
    void GetHeaderParameter(
        QString &prjName, QString &customName);
    // 获取Modbus点表数据
    void GetAllModbusTable(QList<ModbusPointStruct::Point_T> &points);
    // 获取Dlt645点表数据
    void GetAllDlt645Table(QList<Dlt645PointStruct::Point_T> &points);

private slots:
    void on_comboBox_Type_currentTextChanged(const QString &arg1);

    void PrjNameTextEdited_Slot(const QString &text);
    void CustomNameTextEdited_Slot(const QString &text);

private:
    // 表格主体初始化
    void TableWidget_Init();

private:
    Ui::FormPointTable *ui;
    App::PointTabType_E type_;
    QTreeWidgetItem *item_ = nullptr;
    CustomTableWidget *modbus_tab_ = nullptr;
    CustomTableWidget *dlt645_tab_ = nullptr;
};

#endif // FORMPOINTTABLE_H
