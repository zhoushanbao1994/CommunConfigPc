#include "communchs.h"
#include <QDebug>

CommunChs::CommunChs(App::ChType_E type, QObject *parent)
    : QObject(parent)
    , type_(type)
{
    map_ch_.clear();
}

App::ChType_E CommunChs::GetType()
{
    return type_;
}

QMap<QTreeWidgetItem *, FormCommunCh *> *CommunChs::GetMap()
{
    return &map_ch_;
}

void CommunChs::Add(QTreeWidgetItem *item, FormCommunCh *form)
{
    map_ch_.insert(item, form);
}

void CommunChs::Remove(QTreeWidgetItem *item)
{
    qDebug() << __FUNCTION__ << __LINE__ << "删除...";
    // 手动删除指针指向的对象，避免内存泄漏
    for (auto it = map_ch_.begin(); it != map_ch_.end(); ++it) {
        QTreeWidgetItem *tmp_item = it.key();
        FormCommunCh *tmp_form = it.value();
        qDebug() << __FUNCTION__ << __LINE__ << "item:" << tmp_item
                 << ", form:" << tmp_form;
        if((tmp_item == item) && (tmp_form != nullptr)) {
            qDebug() << __FUNCTION__ << __LINE__ << "item:" << tmp_item
                     << ", form:" << tmp_form;
            // 关键步骤 1: 删除值对象 (FormPointTable *)
            delete tmp_form; // 删除 Person 对象
            // 关键步骤 2: 从 map 中移除该键值对
            map_ch_.erase(it);
            break;
        }
    }
}

void CommunChs::RemoveAll()
{
    qDebug() << __FUNCTION__ << __LINE__ << "准备清空 map...";
    int count = 0;

    // 手动删除指针指向的对象，避免内存泄漏
    for (auto it = map_ch_.begin(); it != map_ch_.end(); ++it) {
        QTreeWidgetItem *tmp_item = it.key();
        FormCommunCh * tmp_form = it.value();
        qDebug() << __FUNCTION__ << __LINE__ << "item:" << tmp_item
                 << ", form:" << tmp_form << ", count: " << count++;
        if(tmp_form != nullptr) {
            delete tmp_form; // 删除 Person 对象
        }
    }

    // 清空 map（此时只移除指针本身）
    map_ch_.clear();
    qDebug() << "map 已清空";
}

FormCommunCh *CommunChs::GetForm(QTreeWidgetItem *item)
{
    QMap<QTreeWidgetItem*, FormCommunCh*>::iterator it = map_ch_.find(item);
    if (it != map_ch_.end()) {
        return it.value();
    }
    return nullptr;
}

// 获取所有工程名
QStringList CommunChs::GetAllPrjCustomName()
{
    QStringList name_list;
    // 使用 const_iterator 只读遍历
    QMap<QTreeWidgetItem *, FormCommunCh *>::const_iterator const_it;
    for (const_it = map_ch_.constBegin(); const_it != map_ch_.constEnd(); ++const_it) {
        QTreeWidgetItem *item = const_it.key();
        //FormCommunCh *form = const_it.value();
        name_list.append(item->text(0));
    }

    return name_list;
}

// 获取所有的QTreeWidgetItem*
QList<QTreeWidgetItem *> CommunChs::GetAllTreeWidgetItem()
{
    QList<QTreeWidgetItem *> item_list;
    // 使用 const_iterator 只读遍历
    QMap<QTreeWidgetItem *, FormCommunCh *>::const_iterator const_it;
    for (const_it = map_ch_.constBegin(); const_it != map_ch_.constEnd(); ++const_it) {
        QTreeWidgetItem *item = const_it.key();
        //FormCommunCh *form = const_it.value();
        item_list.append(item);
    }

    return item_list;
}
