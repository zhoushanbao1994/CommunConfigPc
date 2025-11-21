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
        App::ChType_E type, QTreeWidgetItem *item, QString &prj_name, QWidget *parent = nullptr);
    ~FormCommunCh();

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
