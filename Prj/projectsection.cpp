#include "projectsection.h"
#include "ui_projectsection.h"
#include <QMenu>
#include <QDebug>
#include <QList>
#include "app.h"

ProjectSection::ProjectSection(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectSection)
{
    ui->setupUi(this);
    this->initTreeWidget();

    pointTabsModbus_ = new PointTables(App::kPointTabType_Modbus);
    pointTabsDlt645_ = new PointTables(App::kPointTabType_Dlt645);

    chModbusRtu_ = new CommunChs(App::kChType_ModbusRtu);
    chModbusTcp_ = new CommunChs(App::kChType_ModbusTcp);
    chDlt645_ = new CommunChs(App::kChType_Dlt645);

    devModbusRtu_ = new CommunDevs(App::kDevType_ModbusRtu);
    devModbusTcp_ = new CommunDevs(App::kDevType_ModbusTcp);
    devDlt645_ = new CommunDevs(App::kDevType_Dlt645);
}

ProjectSection::~ProjectSection()
{
    delete ui;

    delete pointTabsModbus_;
    delete pointTabsDlt645_;

    delete chModbusRtu_;
    delete chModbusTcp_;
    delete chDlt645_;

    delete devModbusRtu_;
    delete devModbusTcp_;
    delete devDlt645_;
}

void ProjectSection::ClearAll()
{
    pointTabsModbus_->RemoveAll();          // 页面 - Modbus点表
    pointTabsDlt645_->RemoveAll();          // 页面 - Dlt645点表

    chModbusRtu_->RemoveAll();              // 页面 - MRTU通道
    chModbusTcp_->RemoveAll();              // 页面 - MTCP通道
    chDlt645_->RemoveAll();                 // 页面 - DLT645通道

    devModbusRtu_->RemoveAll();             // 页面 - MRTU设备
    devModbusTcp_->RemoveAll();             // 页面 - MTCP设备
    devDlt645_->RemoveAll();                // 页面 - DLT645设备

    RemoveChildItem(twitemPointModbus_);    // 工程栏  - Modbus点表Item
    RemoveChildItem(twitemPointDlt645_);    // 工程栏  - Dlt645点表Item

    RemoveChildItem(twitemChMrtu_);         // 工程栏  - MRTU通道Item
    RemoveChildItem(twitemChMtcp_);         // 工程栏  - MTCP通道Item
    RemoveChildItem(twitemChDlt645_);       // 工程栏  - DLT645通道Item

    RemoveChildItem(twitemDevMrtu_);        // 工程栏  - MRTU设备Item
    RemoveChildItem(twitemDevMtcp_);        // 工程栏  - MTCP设备Item
    RemoveChildItem(twitemDevDlt645_);      // 工程栏  - DLT645设备Item
}

// Modbus点表
void ProjectSection::SetModbusPointTabs(const QMap<QString, ModbusPointStruct::PointTab_T> &mpts)
{
    pointTabsModbus_->RemoveAll();          // 页面 - Modbus点表
    RemoveChildItem(twitemPointModbus_);    // 工程栏  - Modbus点表Item
    QMap<QString, ModbusPointStruct::PointTab_T>::const_iterator it;
    for (it = mpts.cbegin(); it != mpts.cend(); ++it) {
        QString name = it.key();
        ModbusPointStruct::PointTab_T pt = it.value();
        NewPointTab(name, twitemPointModbus_, App::kPointTabType_Modbus, pointTabsModbus_, &pt);
    }
}
// DLT645点表
void ProjectSection::SetDlt645PointTabs(const QMap<QString, Dlt645PointStruct::PointTab_T> &dpts)
{
    pointTabsDlt645_->RemoveAll();          // 页面 - Dlt645点表
    RemoveChildItem(twitemPointDlt645_);    // 工程栏  - Dlt645点表Item
    QMap<QString, Dlt645PointStruct::PointTab_T>::const_iterator it;
    for (it = dpts.cbegin(); it != dpts.cend(); ++it) {
        QString name = it.key();
        Dlt645PointStruct::PointTab_T pt = it.value();
        NewPointTab(name, twitemPointDlt645_, App::kPointTabType_Dlt645, pointTabsDlt645_, &pt);
    }
}
// ModbusRtu通道
void ProjectSection::SetModbusRtuChs(const QMap<QString, ModbusRtuChStruct::Ch_T> &mrcs)
{
    chModbusRtu_->RemoveAll();              // 页面 - MRTU通道
    RemoveChildItem(twitemChMrtu_);         // 工程栏  - MRTU通道Item
    QMap<QString, ModbusRtuChStruct::Ch_T>::const_iterator it;
    for (it = mrcs.cbegin(); it != mrcs.cend(); ++it) {
        QString name = it.key();
        ModbusRtuChStruct::Ch_T ch = it.value();
        NewCommunCh(name, twitemChMrtu_, App::kChType_ModbusRtu, chModbusRtu_, &ch);
    }
}
// ModbusTcp通道
void ProjectSection::SetModbusTcpChs(const QMap<QString, ModbusTcpChStruct::Ch_T> &mtcs)
{
    chModbusTcp_->RemoveAll();              // 页面 - MTCP通道
    RemoveChildItem(twitemChMtcp_);         // 工程栏  - MTCP通道Item
    QMap<QString, ModbusTcpChStruct::Ch_T>::const_iterator it;
    for (it = mtcs.cbegin(); it != mtcs.cend(); ++it) {
        QString name = it.key();
        ModbusTcpChStruct::Ch_T ch = it.value();
        NewCommunCh(name, twitemChMtcp_, App::kChType_ModbusTcp, chModbusTcp_, &ch);
    }
}
// DLT645通道
void ProjectSection::SetDlt645Chs(const QMap<QString, Dlt645ChStruct::Ch_T> &dlcs)
{
    chDlt645_->RemoveAll();                 // 页面 - DLT645通道
    RemoveChildItem(twitemChDlt645_);       // 工程栏  - DLT645通道Item
    QMap<QString, Dlt645ChStruct::Ch_T>::const_iterator it;
    for (it = dlcs.cbegin(); it != dlcs.cend(); ++it) {
        QString name = it.key();
        Dlt645ChStruct::Ch_T ch = it.value();
        NewCommunCh(name, twitemChDlt645_, App::kChType_Dlt645, chDlt645_, &ch);
    }
}
// ModbusRtu设备
void ProjectSection::SetModbusRtuDevs(const QMap<QString, ModbusRtuDevStruct::Dev_T> &mrds)
{
    devModbusRtu_->RemoveAll();             // 页面 - MRTU设备
    RemoveChildItem(twitemDevMrtu_);        // 工程栏  - MRTU设备Item
}
// ModbusTcp设备
void ProjectSection::SetModbusTcpDevs(const QMap<QString, ModbusTcpDevStruct::Dev_T> &mtds)
{
    devModbusTcp_->RemoveAll();             // 页面 - MTCP设备
    RemoveChildItem(twitemDevMtcp_);        // 工程栏  - MTCP设备Item

}
// DLT645设备
void ProjectSection::SetDlt645Devs(const QMap<QString, Dlt645DevStruct::Dev_T> &dlds)
{
    devDlt645_->RemoveAll();                // 页面 - DLT645设备
    RemoveChildItem(twitemDevDlt645_);      // 工程栏  - DLT645设备Item
}

void ProjectSection::RemoveChildItem(QTreeWidgetItem *top_item)
{
    qDebug() << "删除前，顶层节点的子节点数:" << top_item->childCount();
    // 使用 takeChildren() 移除所有子节点
    QList<QTreeWidgetItem *> children = top_item->takeChildren();

    qDebug() << "删除后，顶层节点的子节点数:" << top_item->childCount();
    qDebug() << "从 takeChildren() 返回的子节点数:" << children.size();

    // 遍历并手动删除子节点，释放内存
    qDebug() << "手动删除子节点...";
    qDeleteAll(children); // 这是一个非常方便的 Qt 函数，可以安全地删除列表中的所有指针
    children.clear(); // 清空列表，避免悬挂指针

    qDebug() << "子节点已删除。";
}

void ProjectSection::initTreeWidget()
{
    //ui->treeWidgetProject->header()->setHidden(1);//隐藏最顶上的表头
    ui->treeWidgetProject->clear();
    ui->treeWidgetProject->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->treeWidgetProject->setColumnCount(1);      // 1列
    ui->treeWidgetProject->setColumnWidth(0, 130); // 设置第0列的列宽
    ui->treeWidgetProject->setSortingEnabled(true); // 开启排序功能
    ui->treeWidgetProject->sortByColumn(0, Qt::AscendingOrder); // 按第0列升序排序
    QStringList labels;
    labels << "工程栏";
    ui->treeWidgetProject->setHeaderLabels(labels);

    // 使用右键菜单
    ui->treeWidgetProject->setContextMenuPolicy(Qt::CustomContextMenu);
    // 关联右键事件的信号与槽
    connect(ui->treeWidgetProject, &QTreeWidget::customContextMenuRequested,
            this, &ProjectSection::ShowContextMenu);
    // 关联单击事件的信号槽
    connect(ui->treeWidgetProject, &QTreeWidget::itemClicked,
            this, &ProjectSection::ItemCheckSelf);

    QFont topFont("Arial", 12, QFont::Bold); // 字体：Arial，大小：12，加粗
    QFont topFont2("Arial", 11, QFont::Bold); // 字体：Arial，大小：11，加粗
    // 工程栏  - 点表Item
    twitemPoint_ = new QTreeWidgetItem(
        ui->treeWidgetProject, QStringList(QString("01.通讯点表")));
    twitemPoint_->setFont(0, topFont);
    twitemPointModbus_ = new QTreeWidgetItem(
        twitemPoint_, QStringList(QString("Modbus点表")));
    twitemPointModbus_->setFont(0, topFont2);
    twitemPointDlt645_ = new QTreeWidgetItem(
        twitemPoint_, QStringList(QString("Dlt645点表")));
    twitemPointDlt645_->setFont(0, topFont2);
    twitemPoint_->setExpanded(true);// 展开当前节点

    // 工程栏  - 通道Item
    twitemCh_  = new QTreeWidgetItem(
        ui->treeWidgetProject, QStringList(QString("02.通讯通道")));
    twitemCh_  ->setFont(0, topFont);
    twitemChMrtu_ = new QTreeWidgetItem(
        twitemCh_, QStringList(QString("ModbusRtu通道")));
    twitemChMrtu_->setFont(0, topFont2);
    twitemChMtcp_ = new QTreeWidgetItem(
        twitemCh_, QStringList(QString("ModbusTcp通道")));
    twitemChMtcp_->setFont(0, topFont2);
    twitemChDlt645_ = new QTreeWidgetItem(
        twitemCh_, QStringList(QString("Dlt645通道")));
    twitemChDlt645_->setFont(0, topFont2);
    twitemCh_->setExpanded(true);  // 展开当前节点

    // 工程栏  - 设备Item
    twitemDev_ = new QTreeWidgetItem(
        ui->treeWidgetProject, QStringList(QString("03.通讯设备")));
    twitemDev_ ->setFont(0, topFont);
    twitemDevMrtu_ = new QTreeWidgetItem(
        twitemDev_, QStringList(QString("ModbusRtu设备")));
    twitemDevMrtu_->setFont(0, topFont2);
    twitemDevMtcp_ = new QTreeWidgetItem(
        twitemDev_, QStringList(QString("ModbusTcp设备")));
    twitemDevMtcp_->setFont(0, topFont2);
    twitemDevDlt645_ = new QTreeWidgetItem(
        twitemDev_, QStringList(QString("Dlt645设备")));
    twitemDevDlt645_->setFont(0, topFont2);
    twitemDev_->setExpanded(true);// 展开当前节点

    // 工程栏右键菜单-主Item的菜单
    rightClickMenuMaster_ = new QMenu();
    // 新建
    rightClickActionNew_ = new QAction(tr("新建"),
                                          rightClickMenuMaster_);
    rightClickMenuMaster_->addAction(rightClickActionNew_);
    connect(rightClickActionNew_, &QAction::triggered,
            this, &ProjectSection::RightCheckedActionNew);
    // 工程栏右键菜单-从Item的菜单
    rightClickMenuSlave_ = new QMenu();
    // 删除
    rightClickActionDel_ = new QAction(tr("删除"),
                                         rightClickMenuSlave_);
    rightClickMenuSlave_->addAction(rightClickActionDel_);
    connect(rightClickActionDel_, &QAction::triggered,
            this, &ProjectSection::RightCheckedActionDel);
}

// 点表类型单击，内部处理函数
void ProjectSection::PointTabTypeClick(
    QTreeWidgetItem *item, PointTables *point_tabs, int action)
{
    // 子节点数量
    int count = item->childCount();
    if(count <= 0) {
        return;
    }
    // 取首节点
    QTreeWidgetItem *child_item = item->child(0);
    if(child_item == nullptr) {
        return;
    }
    // 取节点关联的窗口
    FormPointTable *form = point_tabs->GetForm(child_item);
    if(form == nullptr) {
        return;
    }
    // 单击点表类型-发送信号
    emit Form_Signal(form, action); // 单击点表类型
}

// 通道类型单击，内部处理函数
void ProjectSection::CommunChTypeClick(
    QTreeWidgetItem *item, CommunChs *chs, int action)
{
    // 子节点数量
    int count = item->childCount();
    if(count <= 0) {
        return;
    }
    // 取首节点
    QTreeWidgetItem *child_item = item->child(0);
    if(child_item == nullptr) {
        return;
    }
    // 取节点关联的窗口
    FormCommunCh *form = chs->GetForm(child_item);
    if(form == nullptr) {
        return;
    }
    // 单击通道类型-发送信号
    emit Form_Signal(form, action); // 单击通道类型
}

// 设备类型单击，内部处理函数
void ProjectSection::CommunDevTypeClick(
    QTreeWidgetItem *item,  CommunDevs *devs, int action)
{
    // 子节点数量
    int count = item->childCount();
    if(count <= 0) {
        return;
    }
    // 取首节点
    QTreeWidgetItem *child_item = item->child(0);
    if(child_item == nullptr) {
        return;
    }
    // 取节点关联的窗口
    FormCommunDev *form = devs->GetForm(child_item);
    if(form == nullptr) {
        return;
    }
    // 获取指定类型设备依赖的点表工程名，内部处理函数
    QStringList point_tab_name = GetRelyPointTabPrjCustomName(devs);
    // 获取指定类型设备依赖的通道工程名
    QStringList ch_name = GetRelyCommunChPrjCustomName(devs);
    // 刷新页面的下拉选项
    form->RefreshCbOption(point_tab_name, ch_name);
    // 单击设备类型-发送信号
    emit Form_Signal(form, action); // 单击设备类型
}

// 点表子节点查找窗口，内部处理函数
void ProjectSection::PointTabItemFindForm(
    QTreeWidgetItem *item, PointTables *point_tabs, int action, int del)
{
    qDebug() << __FUNCTION__ << item << point_tabs << ", action:" << action << ", del:" << del;
    // 取节点关联的窗口
    FormPointTable *form = point_tabs->GetForm(item);
    if(form == nullptr) {
        return;
    }
    // 子点表单击或右键删除-发送信号
    emit Form_Signal(form, action); // 子点表单击或右键删除
    // 释放窗口内存
    if(del) {
        delete form;
        form = nullptr;
    }
}

// 通道子节点查找窗口，内部处理函数
void ProjectSection::CommunChItemFindForm(
    QTreeWidgetItem *item, CommunChs *chs, int action, int del)
{
    qDebug() << __FUNCTION__ << item << chs << ", action:" << action << ", del:" << del;
    // 取节点关联的窗口
    FormCommunCh *form = chs->GetForm(item);
    if(form == nullptr) {
        return;
    }
    // 子通道单击或右键删除-发送信号
    emit Form_Signal(form, action); // 子通道单击或右键删除
    // 释放窗口内存
    if(del) {
        delete form;
        form = nullptr;
    }
}

// 设备子节点查找窗口，内部处理函数
void ProjectSection::CommunDevItemFindForm(
    QTreeWidgetItem *item,  CommunDevs *devs, int action, int del)
{
    qDebug() << __FUNCTION__ << item << devs << ", action:" << action << ", del:" << del;
    // 取节点关联的窗口
    FormCommunDev *form = devs->GetForm(item);
    if(form == nullptr) {
        return;
    }
    // 获取指定类型设备依赖的点表工程名，内部处理函数
    QStringList point_tab_name = GetRelyPointTabPrjCustomName(devs);
    // 获取指定类型设备依赖的通道工程名
    QStringList ch_name = GetRelyCommunChPrjCustomName(devs);
    // 刷新页面的下拉选项
    form->RefreshCbOption(point_tab_name, ch_name);
    // 子设备单击或右键删除-发送信号
    emit Form_Signal(form, action); // 子设备单击或右键删除
    // 释放窗口内存
    if(del) {
        delete form;
        form = nullptr;
    }
}

// 子节点单击，内部处理函数
void ProjectSection::ItemFindForm(QTreeWidgetItem *item, int action, int del)
{
    QTreeWidgetItem *parent_item = item->parent();
    if(parent_item == nullptr) {
        return;
    }
    if(parent_item == twitemPointDlt645_) {
        PointTabItemFindForm(item, pointTabsDlt645_, action, del);
    }
    else if(parent_item == twitemPointModbus_) {
        PointTabItemFindForm(item, pointTabsModbus_, action, del);
    }
    else if(parent_item == twitemChMrtu_) {
        CommunChItemFindForm(item, chModbusRtu_, action, del);
    }
    else if(parent_item == twitemChMtcp_) {
        CommunChItemFindForm(item, chModbusTcp_, action, del);
    }
    else if(parent_item == twitemChDlt645_) {
        CommunChItemFindForm(item, chDlt645_, action, del);
    }
    else if(parent_item == twitemDevMrtu_) {
        CommunDevItemFindForm(item, devModbusRtu_, action, del);
    }
    else if(parent_item == twitemDevMtcp_) {
        CommunDevItemFindForm(item, devModbusTcp_, action, del);
    }
    else if(parent_item == twitemDevDlt645_) {
        CommunDevItemFindForm(item, devDlt645_, action, del);
    }
}

// TreeWidgetItem 单击事件槽函数
void ProjectSection::ItemCheckSelf(QTreeWidgetItem *item, int column)
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__
             << item->text(column) << column;
    //// 遍历设备信息表
    //foreach(DeviceInfo *info, m_deviceInfos){
    //    // 比较是不是当前点击节点的信息
    //    if(info->getTreeWideItem() != item) {
    //        continue;
    //    }
    //    info->getDevInfoDlg()->hide(); // 信息窗口隐藏（为了使其显示在最前面）
    //    info->getDevInfoDlg()->show(); // 信息窗口显示
    //    return;
    //}
    if((item == twitemPoint_) || (item == twitemCh_) || (item == twitemDev_)) { // 当前操作的是主Item

    }
    else if(item == twitemPointDlt645_) {
        PointTabTypeClick(item, pointTabsDlt645_, 0);
    }
    else if(item == twitemPointModbus_) {
        PointTabTypeClick(item, pointTabsModbus_, 0);
    }
    else if(item == twitemChMrtu_) {
        CommunChTypeClick(item, chModbusRtu_, 0);
    }
    else if(item == twitemChMtcp_) {
        CommunChTypeClick(item, chModbusTcp_, 0);
    }
    else if(item == twitemChDlt645_) {
        CommunChTypeClick(item, chDlt645_, 0);
    }
    else if(item == twitemDevMrtu_) {
        CommunDevTypeClick(item, devModbusRtu_, 0);
    }
    else if(item == twitemDevMtcp_) {
        CommunDevTypeClick(item, devModbusTcp_, 0);
    }
    else if(item == twitemDevDlt645_) {
        CommunDevTypeClick(item, devDlt645_, 0);
    }
    else {
        ItemFindForm(item, 0, 0);
    }
}

// TreeWidget 右键事件槽函数
void ProjectSection::ShowContextMenu(const QPoint& point)
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__
             << point.x() << point.y();

    //QModelIndex curIndex = ui->treeWidget->currentIndex();
    //QModelIndex index = curIndex.sibling(curIndex.row(), 0); //同一行第一列元素的index
    //if(!index.isValid()) {       // 是否有效
    //    return;
    //}
    //ui->treeWidget->expand(index);      // 展开
    ////ui->treeWidget->collapse(index);    // 合拢

    // 当前操作的Item
    QTreeWidgetItem *p = ui->treeWidgetProject->currentItem();
    twitemCurrent_ = p;        // 记录从Item右键时，操作的是哪一个Item
    if((p == twitemPoint_) || (p == twitemCh_) || (p == twitemDev_)) { // 当前操作的是主Item

    }
    else if((p == twitemPointDlt645_) || (p == twitemPointModbus_) ||
        (p == twitemChMrtu_) || (p == twitemChMtcp_) || (p == twitemChDlt645_) ||
        (p == twitemDevMrtu_) || (p == twitemDevMtcp_) || (p == twitemDevDlt645_)) {
        rightClickMenuMaster_->exec(QCursor::pos());// 工程栏右键菜单-主Item的菜单
    }
    else {
        rightClickMenuSlave_->exec(QCursor::pos()); // 工程栏右键菜单-从Item的菜单
    }
}
 // 工程栏右键菜单新建
void ProjectSection::RightCheckedActionNew()
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    // 检查参数
    if(twitemCurrent_ == nullptr) {
        return;
    }

    // 当前操作的是Dlt645点表
    if(twitemCurrent_ == twitemPointDlt645_) {
        NewPointTab("", twitemCurrent_, App::kPointTabType_Dlt645, pointTabsDlt645_, nullptr);
    }
    // 当前操作的是Modbus点表
    else if(twitemCurrent_ == twitemPointModbus_) {
        NewPointTab("", twitemCurrent_, App::kPointTabType_Modbus, pointTabsModbus_, nullptr);
    }
    // 当前操作的是ModbusRtu通讯通道
    else if(twitemCurrent_ == twitemChMrtu_) {
        NewCommunCh("", twitemCurrent_, App::kChType_ModbusRtu, chModbusRtu_, nullptr);
    }
    // 当前操作的是ModbusTcp通讯通道
    else if(twitemCurrent_ == twitemChMtcp_) {
        NewCommunCh("", twitemCurrent_, App::kChType_ModbusTcp, chModbusTcp_, nullptr);
    }
    // 当前操作的是Dlt645通讯通道
    else if(twitemCurrent_ == twitemChDlt645_) {
        NewCommunCh("", twitemCurrent_, App::kChType_Dlt645, chDlt645_, nullptr);
    }
    // 当前操作的是ModbusRtu通讯设备
    else if(twitemCurrent_ == twitemDevMrtu_) {
        NewCommunDev("", twitemCurrent_, App::kDevType_ModbusRtu, devModbusRtu_, nullptr);
    }
    // 当前操作的是ModbusTcp通讯设备
    else if(twitemCurrent_ == twitemDevMtcp_) {
        NewCommunDev("", twitemCurrent_, App::kDevType_ModbusTcp, devModbusTcp_, nullptr);
    }
    // 当前操作的是ModbusRtu通讯设备
    else if(twitemCurrent_ == twitemDevDlt645_) {
        NewCommunDev("", twitemCurrent_, App::kDevType_Dlt645, devDlt645_, nullptr);
    }
    // 未知
    else {

    }
}

// 工程栏右键菜单删除
void ProjectSection::RightCheckedActionDel()
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    // 检查参数
    if(twitemCurrent_ == nullptr) {
        return;
    }
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << twitemCurrent_->text(0);

    // 根据当前子节点，查找对应窗口，并将窗口从页面删除
    ItemFindForm(twitemCurrent_, -1, 0);
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << twitemCurrent_->text(0);
    // 当前节点查找父节点
    QTreeWidgetItem *parent_item = twitemCurrent_->parent();
    if(parent_item == nullptr) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "parent_item == nullptr";
        return;
    }

    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitemCurrent_:" << twitemCurrent_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "parent_item:" << parent_item;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitemPointDlt645_:" << twitemPointDlt645_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitemPointModbus_:" << twitemPointModbus_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitemChMrtu_:" << twitemChMrtu_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitemChMtcp_:" << twitemChMtcp_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitemChDlt645_:" << twitemChDlt645_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitemDevMrtu_:" << twitemDevMrtu_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitemDevMtcp_:" << twitemDevMtcp_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitemDevDlt645_:" << twitemDevDlt645_;
    // 当前父节点是Dlt645点表
    if(parent_item == twitemPointDlt645_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "点表DLT645：parent_item == twitemPointDlt645_";
        pointTabsDlt645_->Remove(twitemCurrent_);
    }
    // 当前父节点是Modbus点表
    else if(parent_item == twitemPointModbus_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "点表Modbus：twitemCurrent_ == twitemPointModbus_";
        pointTabsModbus_->Remove(twitemCurrent_);
    }
    // 当前父节点是ModbusRtu通讯通道
    else if(parent_item == twitemChMrtu_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "通道ModbusRtu：twitemCurrent_ == twitemChMrtu_";
        chModbusRtu_->Remove(twitemCurrent_);
    }
    // 当前父节点是ModbusTcp通讯通道
    else if(parent_item == twitemChMtcp_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "通道ModbusTcp：twitemCurrent_ == twitemChMtcp_";
        chModbusTcp_->Remove(twitemCurrent_);
    }
    // 当前父节点是Dlt645通讯通道
    else if(parent_item == twitemChDlt645_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "通道DLT645：twitemCurrent_ == twitemChDlt645_";
        chDlt645_->Remove(twitemCurrent_);
    }
    // 当前父节点是ModbusRtu通讯设备
    else if(parent_item == twitemDevMrtu_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "设备ModbusRtu：twitemCurrent_ == twitemDevMrtu_";
        devModbusRtu_->Remove(twitemCurrent_);
    }
    // 当前父节点是ModbusTcp通讯设备
    else if(parent_item == twitemDevMtcp_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "设备ModbusTcp：twitemCurrent_ == twitemDevMtcp_";
        devModbusTcp_->Remove(twitemCurrent_);
    }
    // 当前父节点是ModbusRtu通讯设备
    else if(parent_item == twitemDevDlt645_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "设备DLT645：twitemCurrent_ == twitemDevDlt645_";
        devDlt645_->Remove(twitemCurrent_);
    }
    // 未知父节点
    else {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "未知父节点：" << parent_item;
    }
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

    // 从父节点中删除当前子节点
    parent_item->removeChild(twitemCurrent_);
    delete twitemCurrent_;
    twitemCurrent_ = nullptr;
}

/**
 * @brief 判断父节点是否包含指定名称的直接子节点
 * @param parent_item 父节点
 * @param child_name 要查找的子节点名称
 * @param column 要比较的列索引（通常是 0）
 * @return 如果找到，返回 true；否则返回 false
 */
bool ProjectSection::HasChild(const QTreeWidgetItem *parent_item, const QString &child_name, int column)
{
    if (!parent_item) {
        return false; // 父节点为空，直接返回 false
    }
    // 子节点数量
    int count = parent_item->childCount();
    // 遍历所有直接子节点
    for (int i = 0; i < count; i++) {
        QTreeWidgetItem *childItem = parent_item->child(i);
        // 比较子节点在指定列的文本
        if (childItem->text(column) == child_name) {
            return true; // 找到匹配的子节点
        }
    }

    return false; // 遍历完所有子节点都没有找到
}

//// 生成第一个未使用的节点名称
//QString ProjectSection::GenerateUnusedName(const QTreeWidgetItem *item, const QString &name_prefix)
//{
//    for(int i = 1; i < 1000; i++) {
//        // 生成名字
//        QString name = QString("%1%2").arg(name_prefix).arg(i, 3, 10, QChar('0'));
//        // 如果找到同名的，则continue
//        if(HasChild(item, name) == true) {
//            continue;
//        }
//        // 没找到则返回当前名字
//        return name;
//    }
//
//    // 返回空
//    return "";
//}

// 新建点表
void ProjectSection::NewPointTab(QString name,
    QTreeWidgetItem *parent_item, App::PointTabType_E type, PointTables *point_tabs, void *arg)
{
    // 生成随机名称
    QString random_name = (name != "") ? name : App::GenerateRandomString(16);
    qDebug() << __FUNCTION__ << __LINE__ << random_name;
    // 创建子节点
    QTreeWidgetItem *item = new QTreeWidgetItem(parent_item, QStringList(random_name));
    parent_item->setExpanded(true);
    // 创建点表窗口
    FormPointTable *form = new FormPointTable(type, item, random_name);
    // Map存储 节点 与 窗口 的关系
    point_tabs->Add(item, form);
    // 新建点表-发送显示信号
    emit Form_Signal(form, 1);  // 新建点表

    // 是否填充表格内容
    if(arg == nullptr) {
        return;
    }
    if(type == App::kPointTabType_Modbus) {
        ModbusPointStruct::PointTab_T *pt = static_cast<ModbusPointStruct::PointTab_T *>(arg);
        for (int i = 0; i < pt->points.size(); i++) {
            ModbusPointStruct::Point_T point = pt->points.at(i);
            form->ModbusTableWidget_RowSet(i, point.startAddr, point.pointNum,
                    point.code, point.dataType, point.readCycle, point.customName);
        }
    }
    else if(type == App::kPointTabType_Dlt645) {
        Dlt645PointStruct::PointTab_T *pt = static_cast<Dlt645PointStruct::PointTab_T *>(arg);
        for (int i = 0; i < pt->points.size(); i++) {
            Dlt645PointStruct::Point_T point = pt->points.at(i);
            form->Dlt645TableWidget_RowSet(i, point.dataIdent, point.readCycle, point.customName);
        }
    }
}

// 新建通讯通道
void ProjectSection::NewCommunCh(QString name,
    QTreeWidgetItem *parent_item, App::ChType_E type, CommunChs *chs, void *arg)
{
    // 生成随机名称
    QString random_name = (name != "") ? name : App::GenerateRandomString(16);
    qDebug() << __FUNCTION__ << __LINE__ << random_name;
    // 创建子节点
    QTreeWidgetItem *item = new QTreeWidgetItem(parent_item, QStringList(random_name));
    parent_item->setExpanded(true);
    // 创建通讯通道窗口
    FormCommunCh *form = new FormCommunCh(type, item, random_name);
    // Map存储 节点 与 窗口 的关系
    chs->Add(item, form);
    // 新建通道-发送显示信号
    emit Form_Signal(form, 1);  // 新建通道

    // 是否设置页面内容
    if(arg == nullptr) {
        return;
    }
    if(type == App::kChType_ModbusRtu) {
        ModbusRtuChStruct::Ch_T *ch = static_cast<ModbusRtuChStruct::Ch_T *>(arg);
        //qDebug() << __FUNCTION__ << __LINE__
        //         << ch->name << ch->interface << ch->baudRate << ch->dataBits << ch->parity << ch->stopBits;
        // 设置ModbusRtu页面参数
        form->SetModbusRtuPageParameter(ch->interface, ch->baudRate, ch->dataBits, ch->parity, ch->stopBits);
    }
    else if(type == App::kChType_ModbusTcp) {
        ModbusTcpChStruct::Ch_T *ch = static_cast<ModbusTcpChStruct::Ch_T *>(arg);
        //qDebug() << __FUNCTION__ << __LINE__
        //         << ch->name << ch->ip << ch->port;
        // 设置ModbusTcp页面参数
        form->SetModbusTcpPageParameter(ch->ip, ch->port);
    }
    else if(type == App::kChType_Dlt645) {
        Dlt645ChStruct::Ch_T *ch = static_cast<Dlt645ChStruct::Ch_T *>(arg);
        //qDebug() << __FUNCTION__ << __LINE__
        //         << ch->name << ch->interface << ch->baudRate << ch->dataBits << ch->parity << ch->stopBits;
        // 设置DLT645页面参数
        form->SetDlt645PageParameter(ch->interface, ch->baudRate, ch->dataBits, ch->parity, ch->stopBits);
    }
}

// 新建通讯设备
void ProjectSection::NewCommunDev(QString name,
    QTreeWidgetItem *parent_item, App::DevType_E type, CommunDevs *devs, void *arg)
{
    // 生成随机名称
    QString random_name = (name != "") ? name : App::GenerateRandomString(16);
    qDebug() << __FUNCTION__ << __LINE__ << random_name;
    // 创建子节点
    QTreeWidgetItem *item = new QTreeWidgetItem(parent_item, QStringList(random_name));
    parent_item->setExpanded(true);
    // 获取指定类型设备依赖的点表工程名，内部处理函数
    QStringList point_tab_name = GetRelyPointTabPrjCustomName(devs);
    // 获取指定类型设备依赖的通道工程名
    QStringList ch_name = GetRelyCommunChPrjCustomName(devs);
    // 创建通讯通道窗口
    FormCommunDev *form = new FormCommunDev(type, item, random_name);
    form->RefreshCbOption(point_tab_name, ch_name);
    // Map存储 节点 与 窗口 的关系
    devs->Add(item, form);
    // 新建设备-发送显示信号
    emit Form_Signal(form, 1);  // 新建设备
}

// 获取指定类型设备依赖的点表Map，内部处理函数
PointTables *ProjectSection::GetRelyPointTabMap(CommunDevs *devs)
{
    if(devs == devModbusRtu_) {
        return pointTabsModbus_;
    }
    else if(devs == devModbusTcp_) {
        return pointTabsModbus_;
    }
    else if(devs == devDlt645_) {
        return pointTabsDlt645_;
    }
    else {
        return nullptr;
    }
}

// 获取指定类型设备依赖的通道Map，内部处理函数
CommunChs *ProjectSection::GetRelyCommunChMap(CommunDevs *devs)
{
    if(devs == devModbusRtu_) {
        return chModbusRtu_;
    }
    else if(devs == devModbusTcp_) {
        return chModbusTcp_;
    }
    else if(devs == devDlt645_) {
        return chDlt645_;
    }
    else {
        return nullptr;
    }
}

// 获取指定类型设备依赖的点表工程名，内部处理函数
QStringList ProjectSection::GetRelyPointTabPrjCustomName(CommunDevs *devs)
{
    PointTables *point_tab = GetRelyPointTabMap(devs);
    return point_tab->GetAllPrjCustomName();
}

// 获取指定类型设备依赖的通道工程名，内部处理函数
QStringList ProjectSection::GetRelyCommunChPrjCustomName(CommunDevs *devs)
{
    CommunChs *ch = GetRelyCommunChMap(devs);
    return ch->GetAllPrjCustomName();
}
