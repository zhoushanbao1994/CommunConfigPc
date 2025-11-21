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
    void RefreshCbOption(const QStringList &tab_list, const QStringList &ch_list);

private:
    void RefreshMrtuCbOption(const QStringList &tab_list, const QStringList &ch_list);
    void RefreshMtcpCbOption(const QStringList &tab_list, const QStringList &ch_list);
    void RefreshDltCbOption(const QStringList &tab_list, const QStringList &ch_list);

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
