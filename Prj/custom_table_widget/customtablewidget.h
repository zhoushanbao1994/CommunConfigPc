#ifndef CUSTOMTABLEWIDGET_H
#define CUSTOMTABLEWIDGET_H

#include <QObject>
#include <QTableWidget>
#include <QHeaderView>
#include <QColor>
#include <QStringList>
#include <QMenu>
#include <QAction>

class CustomTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    // 构造函数
    explicit CustomTableWidget(QStringList &columnname, int rows = 0, QWidget *parent = nullptr);

signals:
    void InsertLine_Signal(int row_num);

private slots:
    void TableWidget_RightClickMenu(QPoint);
    void TableWidget_RightClickInsertPre();
    void TableWidget_RightClickInsertNext();
    void TableWidget_RightClickRemove();

private:
    // 内部方法：初始化表格样式
    void initStyle(QStringList &columnname);

private:
    //设置菜单选项
    QMenu *pright_click_menu_ = nullptr;
    QAction *paction_insert_pre_ = nullptr;
    QAction *paction_insert_next_ = nullptr;
    QAction *paction_remove_ = nullptr;
};

#endif // CUSTOMTABLEWIDGET_H
