#ifndef HEXDECVALIDATORDELEGATE_H
#define HEXDECVALIDATORDELEGATE_H

#include <QItemDelegate>
#include <QRegExpValidator>
#include <QLineEdit>
#include <QMessageBox>

class HexDecValidatorDelegate : public QItemDelegate {
    Q_OBJECT
public:
    typedef enum ResultFormat_ {
        kResultFormat_Dec = 0,
        kResultFormat_Hex = 1,
    } ResultFormat_E;
public:
    explicit HexDecValidatorDelegate(
        QString &reg, int byte_count = 4, ResultFormat_E format = kResultFormat_Hex, QObject *parent = nullptr);

    // 创建编辑控件（这里用 QLineEdit）
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    // 初始化编辑控件的值（从 QTableWidgetItem 读取值）
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    // 提交编辑后的数据（验证并转换为标准格式）
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    // 更新编辑控件的几何位置
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

private:
    QRegExpValidator *validator_; // 正则验证器

    quint8 bdigit_count_ = 4;       // 十六进制位数
    quint64 max_value_ = 0xFFFF;    // 最大值
    ResultFormat_E result_format_ = kResultFormat_Hex;  // 结果格式
};

#endif /* HEXDECVALIDATORDELEGATE_H */
