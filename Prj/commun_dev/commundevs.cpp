#include "commundevs.h"

CommunDevs::CommunDevs(App::DevType_E type, QObject *parent)
    : QObject(parent)
    , type_(type)
{
    map_dev_.clear();
}

App::DevType_E CommunDevs::GetType()
{
    return type_;
}

QMap<QTreeWidgetItem *, FormCommunDev *> *CommunDevs::GetMap()
{
    return &map_dev_;
}

void CommunDevs::Add(QTreeWidgetItem *item, FormCommunDev *form)
{
    map_dev_.insert(item, form);
}

void CommunDevs::Remove(QTreeWidgetItem *item)
{
    map_dev_.remove(item);
}

FormCommunDev *CommunDevs::GetForm(QTreeWidgetItem *item)
{
    QMap<QTreeWidgetItem*, FormCommunDev*>::iterator it = map_dev_.find(item);
    if (it != map_dev_.end()) {
        return it.value();
    }
    return nullptr;
}

// 获取所有工程名
QStringList CommunDevs::GetAllPrjCustomName()
{
    QStringList name_list;
    // 使用 const_iterator 只读遍历
    QMap<QTreeWidgetItem *, FormCommunDev *>::const_iterator const_it;
    for (const_it = map_dev_.constBegin(); const_it != map_dev_.constEnd(); ++const_it) {
        QTreeWidgetItem *item = const_it.key();
        //FormCommunDev *form = const_it.value();
        name_list.append(item->text(0));
    }

    return name_list;
}
