#ifndef POINTTABLES_H
#define POINTTABLES_H

#include <QObject>
#include <QTreeWidgetItem>
#include "formpointtable.h"
#include "app.h"

class PointTables : public QObject
{
    Q_OBJECT
public:
    PointTables(App::PointTabType_E type, QObject *parent = nullptr);
    App::PointTabType_E GetType();
    QMap<QTreeWidgetItem *, FormPointTable *> *GetMap();
    void Add(QTreeWidgetItem *item, FormPointTable *form);
    void Remove(QTreeWidgetItem *item);
    FormPointTable *GetForm(QTreeWidgetItem *item);
    // 获取所有工程名
    QStringList GetAllPrjName();

private:
    App::PointTabType_E type_;
    QMap<QTreeWidgetItem *, FormPointTable *> map_point_;
};

#endif // POINTTABLES_H
