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
public:
    explicit FormPointTable(
        App::PointTabType_E type, QTreeWidgetItem *item, QString &prj_name,
        QWidget *parent = nullptr);
    ~FormPointTable();
    // 填充一行数据
    void ModbusTableWidget_RowSet(
        int row, quint16 start_addr, quint16 point_num, const QString &code,
        const QString &data_type, int read_cycle, const QString &name);
    // 填充一行数据
    void Dlt645TableWidget_RowSet(
        int row, const QString &code, int read_cycle, const QString &name);

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
