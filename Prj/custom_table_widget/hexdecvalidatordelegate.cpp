#include "hexdecvalidatordelegate.h"

HexDecValidatorDelegate::HexDecValidatorDelegate(
    QString &sreg, int bdigit_count, ResultFormat_E format, QObject *parent)
    : QItemDelegate(parent)
{
    // 正则表达式：匹配十进制（0-65535）或十六进制（0x开头，1-4位十六进制字符）
    QRegExp regExp(sreg);
    validator_ = new QRegExpValidator(regExp, this);

    result_format_ = format;
    bdigit_count_ = bdigit_count;
    switch(bdigit_count) {
    case  1: max_value_ = (quint64)0xF; break;
    case  2: max_value_ = (quint64)0xFF; break;
    case  3: max_value_ = (quint64)0xFFF; break;
    case  4: max_value_ = (quint64)0xFFFF; break;
    case  5: max_value_ = (quint64)0xFFFFF; break;
    case  6: max_value_ = (quint64)0xFFFFFF; break;
    case  7: max_value_ = (quint64)0xFFFFFFF; break;
    case  8: max_value_ = (quint64)0xFFFFFFFF; break;
    case  9: max_value_ = (quint64)0xFFFFFFFFF; break;
    case 10: max_value_ = (quint64)0xFFFFFFFFFF; break;
    case 11: max_value_ = (quint64)0xFFFFFFFFFFF; break;
    case 12: max_value_ = (quint64)0xFFFFFFFFFFFF; break;
    case 13: max_value_ = (quint64)0xFFFFFFFFFFFFF; break;
    case 14: max_value_ = (quint64)0xFFFFFFFFFFFFFF; break;
    case 15: max_value_ = (quint64)0xFFFFFFFFFFFFFFF; break;
    case 16: max_value_ = (quint64)0xFFFFFFFFFFFFFFFF; break;
    default: max_value_ = (quint64)0xFFFF; break;
    }
}

// 创建编辑控件（这里用 QLineEdit）
QWidget *HexDecValidatorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
                      const QModelIndex &) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setValidator(validator_); // 设置输入验证器
    return editor;
}

// 初始化编辑控件的值（从 QTableWidgetItem 读取值）
void HexDecValidatorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    lineEdit->setText(value);
}

// 提交编辑后的数据（验证并转换为标准格式）
void HexDecValidatorDelegate::setModelData(
    QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString input = lineEdit->text().trimmed();

    // 验证输入是否有效（正则已限制格式，这里验证数值范围）
    bool ok;
    quint64 value64; // 用 quint16 存储（0~65535）

    if (input.startsWith("0x", Qt::CaseInsensitive)) {
        // 十六进制转换
        value64 = input.toUInt(&ok, 16);
    } else {
        // 十进制转换
        value64 = input.toUInt(&ok, 10);
    }

    if (ok && value64 <= max_value_) {
        switch(result_format_) {
        case kResultFormat_Dec:
            // 转换成功，设置到模型（这里统一用十进制显示，也可保留十六进制）
            model->setData(index, QString::number(value64), Qt::DisplayRole);
            break;
        case kResultFormat_Hex:
            // 保留十六进制显示（带0x前缀，大写）
            model->setData(index,
                QString("0x") + QString("%1").arg(value64, bdigit_count_, 16, QChar('0')).toUpper(),
                Qt::DisplayRole);
            break;
        default:
            model->setData(index, QString::number(value64), Qt::DisplayRole);
            break;
        }
    } else {
        // 验证失败，弹出提示并恢复原 value
        QMessageBox::warning(editor, "输入错误", "请输入 0~65535（十进制）或 0x0~0xFFFF（十六进制）！");
        // 恢复原 value
        QString originalValue = index.model()->data(index, Qt::DisplayRole).toString();
        model->setData(index, originalValue, Qt::DisplayRole);
    }
}

// 更新编辑控件的几何位置
void HexDecValidatorDelegate::updateEditorGeometry(
    QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
