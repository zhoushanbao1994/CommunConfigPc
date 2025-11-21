#ifndef FORMCOMMUNCH_H
#define FORMCOMMUNCH_H

#include <QWidget>
#include "app.h"

namespace Ui {
class FormCommunCh;
}

class FormCommunCh : public QWidget
{
    Q_OBJECT

public:
    explicit FormCommunCh(App::ChType_E type, QWidget *parent = nullptr);
    ~FormCommunCh();
    void SetPrjName(const QString &name);

private slots:
    void on_comboBox_Type_currentTextChanged(const QString &arg1);

private:
    Ui::FormCommunCh *ui;
    App::ChType_E type_;
};

#endif // FORMCOMMUNCH_H
