#ifndef COMMUNCHS_H
#define COMMUNCHS_H

#include <QObject>
#include <QTreeWidgetItem>
#include "formcommunch.h"
#include "app.h"

class CommunChs : public QObject
{
    Q_OBJECT
public:
    CommunChs(App::ChType_E type, QObject *parent = nullptr);
    App::ChType_E GetType();
    QMap<QTreeWidgetItem *, FormCommunCh *> *GetMap();
    void Add(QTreeWidgetItem *item, FormCommunCh *form);
    void Remove(QTreeWidgetItem *item);
    FormCommunCh *GetForm(QTreeWidgetItem *item);
    // 获取所有工程名
    QStringList GetAllPrjName();

private:
    App::ChType_E type_;
    QMap<QTreeWidgetItem *, FormCommunCh *> map_ch_;

};

#endif // COMMUNCHS_H
