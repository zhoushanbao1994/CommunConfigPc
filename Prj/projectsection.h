#ifndef PROJECTSECTION_H
#define PROJECTSECTION_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "pointtables.h"
#include "communchs.h"
#include "commundevs.h"

namespace Ui {
class ProjectSection;
}

class ProjectSection : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectSection(QWidget *parent = nullptr);
    ~ProjectSection();

signals:
    void Form_Signal(QWidget *form, int action); // action:1新增;0显示,-1删除;

private slots:
    void ItemCheckSelf(QTreeWidgetItem*, int);      // TreeWidgetItem 单击事件槽函数
    void ShowContextMenu(const QPoint&);            // TreeWidget 右键事件槽函数

    void RightCheckedActionNew();                   // 工程栏右键菜单新建
    void RightCheckedActionDel();                   // 工程栏右键菜单删除

private:
    // 判断父节点是否包含指定名称的直接子节点
    bool HasChild(const QTreeWidgetItem *parent_item, const QString &child_name, int column = 0);
    // 生成第一个未使用的节点名称
    QString GenerateUnusedName(const QTreeWidgetItem *item, const QString &name_prefix);
    // 新建点表
    void NewPointTab(QTreeWidgetItem *parent_item,
                    App::PointTabType_E type, QString prj_name_prefix, PointTables *point_tabs);
    // 新建通讯通道
    void NewCommunCh(QTreeWidgetItem *parent_item,
                     App::ChType_E type, QString prj_name_prefix, CommunChs *chs);
    // 新建通讯设备
    void NewCommunDev(QTreeWidgetItem *parent_item,
                      App::DevType_E type, QString prj_name_prefix, CommunDevs *devs);

    // 点表类型单击，内部处理函数
    void PointTabTypeClick(QTreeWidgetItem *item, PointTables *point_tabs, int action);
    // 通道类型单击，内部处理函数
    void CommunChTypeClick(QTreeWidgetItem *item, CommunChs *chs, int action);
    // 设备类型单击，内部处理函数
    void CommunDevTypeClick(QTreeWidgetItem *item, CommunDevs *devs, int action);
    // 点表子节点查找窗口，内部处理函数
    void PointTabItemFindForm(QTreeWidgetItem *item, PointTables *point_tabs, int action, int del);
    // 通道子节点查找窗口，内部处理函数
    void CommunChItemFindForm(QTreeWidgetItem *item, CommunChs *chs, int action, int del);
    // 设备子节点查找窗口，内部处理函数
    void CommunDevItemFindForm(QTreeWidgetItem *item, CommunDevs *devs, int action, int del);
    // 节点查找窗口，内部处理函数
    void ItemFindForm(QTreeWidgetItem *item, int action, int del);
    // 获取指定类型设备依赖的点表Map，内部处理函数
    PointTables *GetRelyPointTabMap(CommunDevs *devs);
    // 获取指定类型设备依赖的通道Map，内部处理函数
    CommunChs *GetRelyCommunChMap(CommunDevs *devs);
    // 获取指定类型设备依赖的点表工程名，内部处理函数
    QStringList GetRelyPointTabPrjName(CommunDevs *devs);
    // 获取指定类型设备依赖的通道工程名，内部处理函数
    QStringList GetRelyCommunChPrjName(CommunDevs *devs);

private:
    void initTreeWidget();
    QTreeWidgetItem *twitem_point_ = nullptr;       // 工程栏  - 点表Item
    QTreeWidgetItem *twitem_pointmodbus_ = nullptr; // 工程栏  - Modbus点表Item
    QTreeWidgetItem *twitem_pointdlt645_ = nullptr; // 工程栏  - Dlt645点表Item
    QTreeWidgetItem *twitem_ch_ = nullptr;          // 工程栏  - 通道Item
    QTreeWidgetItem *twitem_chmrtu_ = nullptr;      // 工程栏  - MRTU通道Item
    QTreeWidgetItem *twitem_chmtcp_ = nullptr;      // 工程栏  - MTCP通道Item
    QTreeWidgetItem *twitem_chdlt645_ = nullptr;    // 工程栏  - DLT645通道Item
    QTreeWidgetItem *twitem_dev_ = nullptr;         // 工程栏  - 设备Item
    QTreeWidgetItem *twitem_devmrtu_ = nullptr;     // 工程栏  - MRTU设备Item
    QTreeWidgetItem *twitem_devmtcp_ = nullptr;     // 工程栏  - MTCP设备Item
    QTreeWidgetItem *twitem_devdlt645_ = nullptr;   // 工程栏  - DLT645设备Item
    QTreeWidgetItem *twitem_current_ = nullptr;     // 当前操作的Item

    QMenu *right_click_menu_master_ = nullptr;      // 工程栏右键菜单-主Item的菜单
    QAction *right_click_action_new_ = nullptr;     // 新建
    QMenu *right_click_menu_slave_ = nullptr;       // 工程栏右键菜单-从Item的菜单
    QAction *right_click_action_del_ = nullptr;     // 删除

private:
    Ui::ProjectSection *ui;

    PointTables *point_tabs_modbus_ = nullptr;
    PointTables *point_tabs_dlt645_ = nullptr;

    CommunChs *ch_modbusrtu_ = nullptr;
    CommunChs *ch_modbustcp_ = nullptr;
    CommunChs *ch_dlt645_ = nullptr;

    CommunDevs *dev_modbusrtu_ = nullptr;
    CommunDevs *dev_modbustcp_ = nullptr;
    CommunDevs *dev_dlt645_ = nullptr;
};

#endif // PROJECTSECTION_H
