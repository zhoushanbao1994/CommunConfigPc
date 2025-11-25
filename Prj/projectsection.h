#ifndef PROJECTSECTION_H
#define PROJECTSECTION_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "pointtables.h"
#include "communchs.h"
#include "commundevs.h"
#include "data_struct/modbuspointstruct.h"
#include "data_struct/dlt645pointstruct.h"
#include "data_struct/modbusrtuchstruct.h"
#include "data_struct/modbustcpchstruct.h"
#include "data_struct/dlt645chstruct.h"
#include "data_struct/modbusrtudevstruct.h"
#include "data_struct/modbustcpdevstruct.h"
#include "data_struct/dlt645devstruct.h"

namespace Ui {
class ProjectSection;
}

class ProjectSection : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectSection(QWidget *parent = nullptr);
    ~ProjectSection();

    void ClearAll();

    void SetModbusPointTabs(const QMap<QString, ModbusPointStruct::PointTab_T> &mpts);// Modbus点表
    void SetDlt645PointTabs(const QMap<QString, Dlt645PointStruct::PointTab_T> &dpts);// DLT645点表

    void SetModbusRtuChs(const QMap<QString, ModbusRtuChStruct::Ch_T> &mrcs);         // ModbusRtu通道
    void SetModbusTcpChs(const QMap<QString, ModbusTcpChStruct::Ch_T> &mtcs);         // ModbusTcp通道
    void SetDlt645Chs(const QMap<QString, Dlt645ChStruct::Ch_T> &dlcs);               // DLT645通道

    void SetModbusRtuDevs(const QMap<QString, ModbusRtuDevStruct::Dev_T> &mrds);      // ModbusRtu设备
    void SetModbusTcpDevs(const QMap<QString, ModbusTcpDevStruct::Dev_T> &mtds);      // ModbusTcp设备
    void SetDlt645Devs(const QMap<QString, Dlt645DevStruct::Dev_T> &dlds);            // DLT645设备

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
    //// 生成第一个未使用的节点名称
    //QString GenerateUnusedName(const QTreeWidgetItem *item, const QString &name_prefix);
    // 新建点表
    void NewPointTab(QString name, QTreeWidgetItem *parent_item,
                    App::PointTabType_E type, PointTables *point_tabs, void *arg);
    // 新建通讯通道
    void NewCommunCh(QString name, QTreeWidgetItem *parent_item,
                     App::ChType_E type, CommunChs *chs, void *arg);
    // 新建通讯设备
    void NewCommunDev(QString name, QTreeWidgetItem *parent_item,
                      App::DevType_E type, CommunDevs *devs, void *arg);

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
    QStringList GetRelyPointTabPrjCustomName(CommunDevs *devs);
    // 获取指定类型设备依赖的通道工程名，内部处理函数
    QStringList GetRelyCommunChPrjCustomName(CommunDevs *devs);

    // 移除子节点，并作内存释放，内部处理函数
    void RemoveChildItem(QTreeWidgetItem *top_item);

private:
    void initTreeWidget();
    QTreeWidgetItem *twitemPoint_ = nullptr;        // 工程栏  - 点表Item
    QTreeWidgetItem *twitemPointModbus_ = nullptr;  // 工程栏  - Modbus点表Item
    QTreeWidgetItem *twitemPointDlt645_ = nullptr;  // 工程栏  - Dlt645点表Item
    QTreeWidgetItem *twitemCh_ = nullptr;           // 工程栏  - 通道Item
    QTreeWidgetItem *twitemChMrtu_ = nullptr;       // 工程栏  - MRTU通道Item
    QTreeWidgetItem *twitemChMtcp_ = nullptr;       // 工程栏  - MTCP通道Item
    QTreeWidgetItem *twitemChDlt645_ = nullptr;     // 工程栏  - DLT645通道Item
    QTreeWidgetItem *twitemDev_ = nullptr;          // 工程栏  - 设备Item
    QTreeWidgetItem *twitemDevMrtu_ = nullptr;      // 工程栏  - MRTU设备Item
    QTreeWidgetItem *twitemDevMtcp_ = nullptr;      // 工程栏  - MTCP设备Item
    QTreeWidgetItem *twitemDevDlt645_ = nullptr;    // 工程栏  - DLT645设备Item
    QTreeWidgetItem *twitemCurrent_ = nullptr;      // 当前操作的Item

    QMenu *rightClickMenuMaster_ = nullptr;         // 工程栏右键菜单-主Item的菜单
    QAction *rightClickActionNew_ = nullptr;        // 新建
    QMenu *rightClickMenuSlave_ = nullptr;          // 工程栏右键菜单-从Item的菜单
    QAction *rightClickActionDel_ = nullptr;        // 删除

private:
    Ui::ProjectSection *ui;

    PointTables *pointTabsModbus_ = nullptr;
    PointTables *pointTabsDlt645_ = nullptr;

    CommunChs *chModbusRtu_ = nullptr;
    CommunChs *chModbusTcp_ = nullptr;
    CommunChs *chDlt645_ = nullptr;

    CommunDevs *devModbusRtu_ = nullptr;
    CommunDevs *devModbusTcp_ = nullptr;
    CommunDevs *devDlt645_ = nullptr;
};

#endif // PROJECTSECTION_H
