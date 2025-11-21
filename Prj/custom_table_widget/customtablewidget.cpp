#include "customtablewidget.h"
#include <QDebug>

// 构造函数
CustomTableWidget::CustomTableWidget(QStringList &columnname, int rows, QWidget *parent)
    : QTableWidget(rows, columnname.count(), parent)
{
    initStyle(columnname);
}

// 初始化表格样式
void CustomTableWidget::initStyle(QStringList &columnname)
{
    /*设置表格是否充满，即行末不留空*/
    horizontalHeader()->setStretchLastSection(true);
    /*设置tablewidget等宽*/
    //horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 设置表格内容不可编辑
    //ui->tableWidget_ModbusPointTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 表格使用交替色填充
    setAlternatingRowColors(true);
    setStyleSheet("QTableWidget { alternate-background-color: #F0F0F0; }");
    setStyleSheet("QHeaderView::section { background-color: #4A4A4A; color: #FFFFFF; padding: 2px; border: 1px solid #666666; }");
    // 行选中模式
    setSelectionBehavior(QAbstractItemView::SelectRows);
    //开启捕获鼠标功能
    setMouseTracking(true);

    // 隐藏行头
    verticalHeader()->hide();

    // 设置指定行行高
    //verticalHeader()->resizeSection(1,110);

    //  设置列头
    setHorizontalHeaderLabels(columnname);

    //设置指定列列宽
    QHeaderView *pHead = horizontalHeader();
    //pHead->setSectionResizeMode(QHeaderView::Interactive);
    int column = columnCount();
    for(int col = 0; col < column-1; col++) {
        pHead->resizeSection(col, 80);
    }

    // 设置控件的上下文菜单（右键菜单）策略:自定义上下文菜单
    setContextMenuPolicy (Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested,
            this, &CustomTableWidget::TableWidget_RightClickMenu);

    pright_click_menu_ = new QMenu(this);
    paction_insert_pre_ = new QAction("插入前一行", this);
    paction_insert_next_ = new QAction("插入后一行", this);
    paction_remove_ = new QAction("删除", this);
    pright_click_menu_->addAction(paction_insert_pre_);
    pright_click_menu_->addAction(paction_insert_next_);
    pright_click_menu_->addAction(paction_remove_);
    connect (paction_insert_pre_, &QAction::triggered,
            this, &CustomTableWidget::TableWidget_RightClickInsertPre);
    connect (paction_insert_next_, &QAction::triggered,
            this, &CustomTableWidget::TableWidget_RightClickInsertNext);
    connect (paction_remove_, &QAction::triggered,
            this, &CustomTableWidget::TableWidget_RightClickRemove);
}

// 表格右键菜单槽函数
void CustomTableWidget::TableWidget_RightClickMenu(QPoint p)
{
    // 获得QTableWidget列表点击的行数
    int currRow  = indexAt(p).row ();
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << p << currRow;

    pright_click_menu_->move (cursor ().pos ());
    pright_click_menu_->show ();
}

// 表格右键菜单插入槽函数
void CustomTableWidget::TableWidget_RightClickInsertPre()
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    int currRow = currentRow();
    insertRow(currRow);
    emit InsertLine_Signal(currRow);
}
// 表格右键菜单插入槽函数
void CustomTableWidget::TableWidget_RightClickInsertNext()
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    int currRow = currentRow();
    insertRow(currRow+1);
    emit InsertLine_Signal(currRow+1);
}
// 表格右键菜单删除槽函数
void CustomTableWidget::TableWidget_RightClickRemove()
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    int currRow = currentRow();
    removeRow(currRow);        // 删除行
}

