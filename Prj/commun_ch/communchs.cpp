#include "communchs.h"

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
    map_ch_.remove(item);
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
QStringList CommunChs::GetAllPrjName()
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
