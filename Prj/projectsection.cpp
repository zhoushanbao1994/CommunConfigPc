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

    point_tabs_modbus_ = new PointTables(App::kPointTabType_Modbus);
    point_tabs_dlt645_ = new PointTables(App::kPointTabType_Dlt645);

    ch_modbusrtu_ = new CommunChs(App::kChType_ModbusRtu);
    ch_modbustcp_ = new CommunChs(App::kChType_ModbusTcp);
    ch_dlt645_ = new CommunChs(App::kChType_Dlt645);

    dev_modbusrtu_ = new CommunDevs(App::kDevType_ModbusRtu);
    dev_modbustcp_ = new CommunDevs(App::kDevType_ModbusTcp);
    dev_dlt645_ = new CommunDevs(App::kDevType_Dlt645);
}

ProjectSection::~ProjectSection()
{
    delete ui;

    delete point_tabs_modbus_;
    delete point_tabs_dlt645_;

    delete ch_modbusrtu_;
    delete ch_modbustcp_;
    delete ch_dlt645_;

    delete dev_modbusrtu_;
    delete dev_modbustcp_;
    delete dev_dlt645_;
}

void ProjectSection::ClearAll()
{
    point_tabs_modbus_->RemoveAll();
    point_tabs_dlt645_->RemoveAll();

    ch_modbusrtu_->RemoveAll();
    ch_modbustcp_->RemoveAll();
    ch_dlt645_->RemoveAll();

    dev_modbusrtu_->RemoveAll();
    dev_modbustcp_->RemoveAll();
    dev_dlt645_->RemoveAll();

    RemoveChildItem(twitem_pointmodbus_);   // 工程栏  - Modbus点表Item
    RemoveChildItem(twitem_pointdlt645_);   // 工程栏  - Dlt645点表Item

    RemoveChildItem(twitem_chmrtu_);        // 工程栏  - MRTU通道Item
    RemoveChildItem(twitem_chmtcp_);        // 工程栏  - MTCP通道Item
    RemoveChildItem(twitem_chdlt645_);      // 工程栏  - DLT645通道Item

    RemoveChildItem(twitem_devmrtu_);       // 工程栏  - MRTU设备Item
    RemoveChildItem(twitem_devmtcp_);       // 工程栏  - MTCP设备Item
    RemoveChildItem(twitem_devdlt645_);     // 工程栏  - DLT645设备Item
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
    twitem_point_ = new QTreeWidgetItem(
        ui->treeWidgetProject, QStringList(QString("01.通讯点表")));
    twitem_point_->setFont(0, topFont);
    twitem_pointmodbus_ = new QTreeWidgetItem(
        twitem_point_, QStringList(QString("Modbus点表")));
    twitem_pointmodbus_->setFont(0, topFont2);
    twitem_pointdlt645_ = new QTreeWidgetItem(
        twitem_point_, QStringList(QString("Dlt645点表")));
    twitem_pointdlt645_->setFont(0, topFont2);
    twitem_point_->setExpanded(true);// 展开当前节点

    // 工程栏  - 通道Item
    twitem_ch_  = new QTreeWidgetItem(
        ui->treeWidgetProject, QStringList(QString("02.通讯通道")));
    twitem_ch_  ->setFont(0, topFont);
    twitem_chmrtu_ = new QTreeWidgetItem(
        twitem_ch_, QStringList(QString("ModbusRtu通道")));
    twitem_chmrtu_->setFont(0, topFont2);
    twitem_chmtcp_ = new QTreeWidgetItem(
        twitem_ch_, QStringList(QString("ModbusTcp通道")));
    twitem_chmtcp_->setFont(0, topFont2);
    twitem_chdlt645_ = new QTreeWidgetItem(
        twitem_ch_, QStringList(QString("Dlt645通道")));
    twitem_chdlt645_->setFont(0, topFont2);
    twitem_ch_->setExpanded(true);  // 展开当前节点

    // 工程栏  - 设备Item
    twitem_dev_ = new QTreeWidgetItem(
        ui->treeWidgetProject, QStringList(QString("03.通讯设备")));
    twitem_dev_ ->setFont(0, topFont);
    twitem_devmrtu_ = new QTreeWidgetItem(
        twitem_dev_, QStringList(QString("ModbusRtu设备")));
    twitem_devmrtu_->setFont(0, topFont2);
    twitem_devmtcp_ = new QTreeWidgetItem(
        twitem_dev_, QStringList(QString("ModbusTcp设备")));
    twitem_devmtcp_->setFont(0, topFont2);
    twitem_devdlt645_ = new QTreeWidgetItem(
        twitem_dev_, QStringList(QString("Dlt645设备")));
    twitem_devdlt645_->setFont(0, topFont2);
    twitem_dev_->setExpanded(true);// 展开当前节点

    // 工程栏右键菜单-主Item的菜单
    right_click_menu_master_ = new QMenu();
    // 新建
    right_click_action_new_ = new QAction(tr("新建"),
                                          right_click_menu_master_);
    right_click_menu_master_->addAction(right_click_action_new_);
    connect(right_click_action_new_, &QAction::triggered,
            this, &ProjectSection::RightCheckedActionNew);
    // 工程栏右键菜单-从Item的菜单
    right_click_menu_slave_ = new QMenu();
    // 删除
    right_click_action_del_ = new QAction(tr("删除"),
                                         right_click_menu_slave_);
    right_click_menu_slave_->addAction(right_click_action_del_);
    connect(right_click_action_del_, &QAction::triggered,
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
    if(parent_item == twitem_pointdlt645_) {
        PointTabItemFindForm(item, point_tabs_dlt645_, action, del);
    }
    else if(parent_item == twitem_pointmodbus_) {
        PointTabItemFindForm(item, point_tabs_modbus_, action, del);
    }
    else if(parent_item == twitem_chmrtu_) {
        CommunChItemFindForm(item, ch_modbusrtu_, action, del);
    }
    else if(parent_item == twitem_chmtcp_) {
        CommunChItemFindForm(item, ch_modbustcp_, action, del);
    }
    else if(parent_item == twitem_chdlt645_) {
        CommunChItemFindForm(item, ch_dlt645_, action, del);
    }
    else if(parent_item == twitem_devmrtu_) {
        CommunDevItemFindForm(item, dev_modbusrtu_, action, del);
    }
    else if(parent_item == twitem_devmtcp_) {
        CommunDevItemFindForm(item, dev_modbustcp_, action, del);
    }
    else if(parent_item == twitem_devdlt645_) {
        CommunDevItemFindForm(item, dev_dlt645_, action, del);
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
    if((item == twitem_point_) || (item == twitem_ch_) || (item == twitem_dev_)) { // 当前操作的是主Item

    }
    else if(item == twitem_pointdlt645_) {
        PointTabTypeClick(item, point_tabs_dlt645_, 0);
    }
    else if(item == twitem_pointmodbus_) {
        PointTabTypeClick(item, point_tabs_modbus_, 0);
    }
    else if(item == twitem_chmrtu_) {
        CommunChTypeClick(item, ch_modbusrtu_, 0);
    }
    else if(item == twitem_chmtcp_) {
        CommunChTypeClick(item, ch_modbustcp_, 0);
    }
    else if(item == twitem_chdlt645_) {
        CommunChTypeClick(item, ch_dlt645_, 0);
    }
    else if(item == twitem_devmrtu_) {
        CommunDevTypeClick(item, dev_modbusrtu_, 0);
    }
    else if(item == twitem_devmtcp_) {
        CommunDevTypeClick(item, dev_modbustcp_, 0);
    }
    else if(item == twitem_devdlt645_) {
        CommunDevTypeClick(item, dev_dlt645_, 0);
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
    twitem_current_ = p;        // 记录从Item右键时，操作的是哪一个Item
    if((p == twitem_point_) || (p == twitem_ch_) || (p == twitem_dev_)) { // 当前操作的是主Item

    }
    else if((p == twitem_pointdlt645_) || (p == twitem_pointmodbus_) ||
        (p == twitem_chmrtu_) || (p == twitem_chmtcp_) || (p == twitem_chdlt645_) ||
        (p == twitem_devmrtu_) || (p == twitem_devmtcp_) || (p == twitem_devdlt645_)) {
        right_click_menu_master_->exec(QCursor::pos()); // 工程栏右键菜单-主Item的菜单
    }
    else {
        right_click_menu_slave_->exec(QCursor::pos());// 工程栏右键菜单-从Item的菜单
    }
}
 // 工程栏右键菜单新建
void ProjectSection::RightCheckedActionNew()
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    // 检查参数
    if(twitem_current_ == nullptr) {
        return;
    }

    // 当前操作的是Dlt645点表
    if(twitem_current_ == twitem_pointdlt645_) {
        NewPointTab(twitem_current_, App::kPointTabType_Dlt645, point_tabs_dlt645_);
    }
    // 当前操作的是Modbus点表
    else if(twitem_current_ == twitem_pointmodbus_) {
        NewPointTab(twitem_current_, App::kPointTabType_Modbus, point_tabs_modbus_);
    }
    // 当前操作的是ModbusRtu通讯通道
    else if(twitem_current_ == twitem_chmrtu_) {
        NewCommunCh(twitem_current_, App::kChType_ModbusRtu, ch_modbusrtu_);
    }
    // 当前操作的是ModbusTcp通讯通道
    else if(twitem_current_ == twitem_chmtcp_) {
        NewCommunCh(twitem_current_, App::kChType_ModbusTcp, ch_modbustcp_);
    }
    // 当前操作的是Dlt645通讯通道
    else if(twitem_current_ == twitem_chdlt645_) {
        NewCommunCh(twitem_current_, App::kChType_Dlt645, ch_dlt645_);
    }
    // 当前操作的是ModbusRtu通讯设备
    else if(twitem_current_ == twitem_devmrtu_) {
        NewCommunDev(twitem_current_, App::kDevType_ModbusRtu, dev_modbusrtu_);
    }
    // 当前操作的是ModbusTcp通讯设备
    else if(twitem_current_ == twitem_devmtcp_) {
        NewCommunDev(twitem_current_, App::kDevType_ModbusTcp, dev_modbustcp_);
    }
    // 当前操作的是ModbusRtu通讯设备
    else if(twitem_current_ == twitem_devdlt645_) {
        NewCommunDev(twitem_current_, App::kDevType_Dlt645, dev_dlt645_);
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
    if(twitem_current_ == nullptr) {
        return;
    }
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << twitem_current_->text(0);

    // 根据当前子节点，查找对应窗口，并将窗口从页面删除
    ItemFindForm(twitem_current_, -1, 0);
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << twitem_current_->text(0);
    // 当前节点查找父节点
    QTreeWidgetItem *parent_item = twitem_current_->parent();
    if(parent_item == nullptr) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "parent_item == nullptr";
        return;
    }

    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitem_current_:" << twitem_current_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "parent_item:" << parent_item;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitem_pointdlt645_:" << twitem_pointdlt645_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitem_pointmodbus_:" << twitem_pointmodbus_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitem_chmrtu_:" << twitem_chmrtu_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitem_chmtcp_:" << twitem_chmtcp_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitem_chdlt645_:" << twitem_chdlt645_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitem_devmrtu_:" << twitem_devmrtu_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitem_devmtcp_:" << twitem_devmtcp_;
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "twitem_devdlt645_:" << twitem_devdlt645_;
    // 当前父节点是Dlt645点表
    if(parent_item == twitem_pointdlt645_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "点表DLT645：parent_item == twitem_pointdlt645_";
        point_tabs_dlt645_->Remove(twitem_current_);
    }
    // 当前父节点是Modbus点表
    else if(parent_item == twitem_pointmodbus_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "点表Modbus：twitem_current_ == twitem_pointmodbus_";
        point_tabs_modbus_->Remove(twitem_current_);
    }
    // 当前父节点是ModbusRtu通讯通道
    else if(parent_item == twitem_chmrtu_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "通道ModbusRtu：twitem_current_ == twitem_chmrtu_";
        ch_modbusrtu_->Remove(twitem_current_);
    }
    // 当前父节点是ModbusTcp通讯通道
    else if(parent_item == twitem_chmtcp_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "通道ModbusTcp：twitem_current_ == twitem_chmtcp_";
        ch_modbustcp_->Remove(twitem_current_);
    }
    // 当前父节点是Dlt645通讯通道
    else if(parent_item == twitem_chdlt645_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "通道DLT645：twitem_current_ == twitem_chdlt645_";
        ch_dlt645_->Remove(twitem_current_);
    }
    // 当前父节点是ModbusRtu通讯设备
    else if(parent_item == twitem_devmrtu_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "设备ModbusRtu：twitem_current_ == twitem_devmrtu_";
        dev_modbusrtu_->Remove(twitem_current_);
    }
    // 当前父节点是ModbusTcp通讯设备
    else if(parent_item == twitem_devmtcp_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "设备ModbusTcp：twitem_current_ == twitem_devmtcp_";
        dev_modbustcp_->Remove(twitem_current_);
    }
    // 当前父节点是ModbusRtu通讯设备
    else if(parent_item == twitem_devdlt645_) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "设备DLT645：twitem_current_ == twitem_devdlt645_";
        dev_dlt645_->Remove(twitem_current_);
    }
    // 未知父节点
    else {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "未知父节点：" << parent_item;
    }
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

    // 从父节点中删除当前子节点
    parent_item->removeChild(twitem_current_);
    delete twitem_current_;
    twitem_current_ = nullptr;
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
void ProjectSection::NewPointTab(
    QTreeWidgetItem *parent_item, App::PointTabType_E type, PointTables *point_tabs)
{
    // 生成随机名称
    QString random_name = App::GenerateRandomString(16);
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
}

// 新建通讯通道
void ProjectSection::NewCommunCh(
    QTreeWidgetItem *parent_item, App::ChType_E type, CommunChs *chs)
{
    // 生成随机名称
    QString random_name = App::GenerateRandomString(16);
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
}

// 新建通讯设备
void ProjectSection::NewCommunDev(
    QTreeWidgetItem *parent_item, App::DevType_E type, CommunDevs *devs)
{
    // 生成随机名称
    QString random_name = App::GenerateRandomString(16);
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
    if(devs == dev_modbusrtu_) {
        return point_tabs_modbus_;
    }
    else if(devs == dev_modbustcp_) {
        return point_tabs_modbus_;
    }
    else if(devs == dev_dlt645_) {
        return point_tabs_dlt645_;
    }
    else {
        return nullptr;
    }
}

// 获取指定类型设备依赖的通道Map，内部处理函数
CommunChs *ProjectSection::GetRelyCommunChMap(CommunDevs *devs)
{
    if(devs == dev_modbusrtu_) {
        return ch_modbusrtu_;
    }
    else if(devs == dev_modbustcp_) {
        return ch_modbustcp_;
    }
    else if(devs == dev_dlt645_) {
        return ch_dlt645_;
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
