#ifndef FORMCOMMUNDEV_H
#define FORMCOMMUNDEV_H

#include <QWidget>
#include "app.h"

namespace Ui {
class FormCommunDev;
}

class FormCommunDev : public QWidget
{
    Q_OBJECT

public:
    explicit FormCommunDev(App::DevType_E type, QWidget *parent = nullptr);
    ~FormCommunDev();
    void SetPrjName(const QString &name);
    void RefreshCbOption(const QStringList &tab_list, const QStringList &ch_list);

private:
    void RefreshMrtuCbOption(const QStringList &tab_list, const QStringList &ch_list);
    void RefreshMtcpCbOption(const QStringList &tab_list, const QStringList &ch_list);
    void RefreshDltCbOption(const QStringList &tab_list, const QStringList &ch_list);

private slots:
    void on_comboBox_Type_currentTextChanged(const QString &arg1);

private:
    Ui::FormCommunDev *ui;
    App::DevType_E type_;
};

#endif // FORMCOMMUNDEV_H
