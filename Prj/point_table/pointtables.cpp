#include "pointtables.h"

PointTables::PointTables(App::PointTabType_E type, QObject *parent)
    : QObject(parent)
    , type_(type)
{
    map_point_.clear();
}

App::PointTabType_E PointTables::GetType()
{
    return type_;
}

QMap<QTreeWidgetItem *, FormPointTable *> *PointTables::GetMap()
{
    return &map_point_;
}

void PointTables::Add(QTreeWidgetItem *item, FormPointTable *form)
{
    map_point_.insert(item, form);
}

void PointTables::Remove(QTreeWidgetItem *item)
{
    map_point_.remove(item);
}

FormPointTable *PointTables::GetForm(QTreeWidgetItem *item)
{
    QMap<QTreeWidgetItem*, FormPointTable*>::iterator it = map_point_.find(item);
    if (it != map_point_.end()) {
        return it.value();
    }
    return nullptr;
}

// 获取所有工程名
QStringList PointTables::GetAllPrjName()
{
    QStringList name_list;
    // 使用 const_iterator 只读遍历
    QMap<QTreeWidgetItem *, FormPointTable *>::const_iterator const_it;
    for (const_it = map_point_.constBegin(); const_it != map_point_.constEnd(); ++const_it) {
        QTreeWidgetItem *item = const_it.key();
        //FormPointTable *form = const_it.value();
        name_list.append(item->text(0));
    }

    return name_list;
}
