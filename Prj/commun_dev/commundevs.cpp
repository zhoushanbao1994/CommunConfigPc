#include "commundevs.h"
#include <QDebug>

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
    qDebug() << __FUNCTION__ << __LINE__ << "删除...";
    // 手动删除指针指向的对象，避免内存泄漏
    for (auto it = map_dev_.begin(); it != map_dev_.end(); ++it) {
        QTreeWidgetItem *tmp_item = it.key();
        FormCommunDev *tmp_form = it.value();
        qDebug() << __FUNCTION__ << __LINE__ << "item:" << tmp_item
                 << ", form:" << tmp_form;
        if((tmp_item == item) && (tmp_form != nullptr)) {
            qDebug() << __FUNCTION__ << __LINE__ << "item:" << tmp_item
                     << ", form:" << tmp_form;
            // 关键步骤 1: 删除值对象 (FormPointTable *)
            delete tmp_form; // 删除 Person 对象
            // 关键步骤 2: 从 map 中移除该键值对
            map_dev_.erase(it);
            break;
        }
    }
}

void CommunDevs::RemoveAll()
{
    qDebug() << __FUNCTION__ << __LINE__ << "准备清空 map...";
    int count = 0;

    // 手动删除指针指向的对象，避免内存泄漏
    for (auto it = map_dev_.begin(); it != map_dev_.end(); ++it) {
        QTreeWidgetItem *tmp_item = it.key();
        FormCommunDev *tmp_form = it.value();
        qDebug() << __FUNCTION__ << __LINE__ << "item:" << tmp_item
                 << ", form:" << tmp_form << ", count: " << count++;
        if(tmp_form != nullptr) {
            delete tmp_form; // 删除 Person 对象
        }
    }

    // 清空 map（此时只移除指针本身）
    map_dev_.clear();
    qDebug() << "map 已清空";
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
