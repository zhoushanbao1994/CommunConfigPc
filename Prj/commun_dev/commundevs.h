#ifndef COMMUNDEVS_H
#define COMMUNDEVS_H

#include <QObject>
#include <QTreeWidgetItem>
#include "formcommundev.h"
#include "app.h"

class CommunDevs : public QObject
{
    Q_OBJECT
public:
    CommunDevs(App::DevType_E type, QObject *parent = nullptr);
    App::DevType_E GetType();
    QMap<QTreeWidgetItem *, FormCommunDev *> *GetMap();
    void Add(QTreeWidgetItem *item, FormCommunDev *form);
    void Remove(QTreeWidgetItem *item);
    FormCommunDev *GetForm(QTreeWidgetItem *item);
    // 获取所有工程名
    QStringList GetAllPrjName();

private:
    App::DevType_E type_;
    QMap<QTreeWidgetItem *, FormCommunDev *> map_dev_;
};

#endif // COMMUNDEVS_H
