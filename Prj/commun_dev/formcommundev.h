#ifndef FORMCOMMUNDEV_H
#define FORMCOMMUNDEV_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "app.h"

namespace Ui {
class FormCommunDev;
}

class FormCommunDev : public QWidget
{
    Q_OBJECT

public:
    explicit FormCommunDev(
        App::DevType_E type, QTreeWidgetItem *item, QString &prj_name,
        QWidget *parent = nullptr);
    ~FormCommunDev();

    // 刷新下拉框选项
    void RefreshCbOption(const QStringList &tab_list, const QStringList &ch_list);

    // 设置页面参数
    void SetPageParameter(
        const QString &point, const QString &ch, const QString &addr);

private:
    // 刷新ModbusRtu页面下拉框选项
    void RefreshMrtuCbOption(const QStringList &tab_list, const QStringList &ch_list);
    // 刷新ModbusTcp页面下拉框选项
    void RefreshMtcpCbOption(const QStringList &tab_list, const QStringList &ch_list);
    // 刷新Dlt645页面下拉框选项
    void RefreshDltCbOption(const QStringList &tab_list, const QStringList &ch_list);

    // 设置ModbusRtu页面参数
    void SetModbusRtuPageParameter(
        const QString &point, const QString &ch, quint8 addr);
    // 设置ModbusTcp页面参数
    void SetModbusTcpPageParameter(
        const QString &point, const QString &ch, quint8 addr);
    // 设置DLT645页面参数
    void SetDlt645PageParameter(
        const QString &point, const QString &ch, const QString &addr);

private slots:
    void on_comboBox_Type_currentTextChanged(const QString &arg1);

    void PrjNameTextEdited_Slot(const QString &text);
    void CustomNameTextEdited_Slot(const QString &text);

private:
    Ui::FormCommunDev *ui;
    App::DevType_E type_;
    QTreeWidgetItem *item_ = nullptr;
};

#endif // FORMCOMMUNDEV_H
