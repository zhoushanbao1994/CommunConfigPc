#ifndef FORMCOMMUNCH_H
#define FORMCOMMUNCH_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "app.h"

namespace Ui {
class FormCommunCh;
}

class FormCommunCh : public QWidget
{
    Q_OBJECT

public:
    explicit FormCommunCh(
        App::ChType_E type, QTreeWidgetItem *item,  QString &prjName,
        QString &customName, QWidget *parent = nullptr);
    ~FormCommunCh();

    // 设置ModbusRtu页面参数
    void SetModbusRtuPageParameter(
        const QString &interface, const QString &baudRate,
        const QString &dataBits, const QString &parity, const QString &stopBits);
    // 设置ModbusTcp页面参数
    void SetModbusTcpPageParameter(
        const QString &ip, quint16 port);
    // 设置DLT645页面参数
    void SetDlt645PageParameter(
        const QString &interface, const QString &baudRate,
        const QString &dataBits, const QString &parity, const QString &stopBits);

    // 获取页头参数
    void GetHeaderParameter(
        QString &prjName, QString &customName);
    // 获取ModbusRtu页面参数
    void GetModbusRtuPageParameter(
        QString &interface, QString &baudRate,
        QString &dataBits, QString &parity, QString &stopBits);
    // 获取ModbusTcp页面参数
    void GetModbusTcpPageParameter(
        QString &ip, quint16 &port);
    // 获取DLT645页面参数
    void GetDlt645PageParameter(
        QString &interface, QString &baudRate,
        QString &dataBits, QString &parity, QString &stopBits);

private slots:
    void on_comboBox_Type_currentTextChanged(const QString &arg1);

    void PrjNameTextEdited_Slot(const QString &text);
    void CustomNameTextEdited_Slot(const QString &text);

private:
    Ui::FormCommunCh *ui;
    App::ChType_E type_;
    QTreeWidgetItem *item_ = nullptr;
};

#endif // FORMCOMMUNCH_H
