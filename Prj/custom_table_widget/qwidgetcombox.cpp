#include "qwidgetcombox.h"
#include <QHBoxLayout>

QWidgetComBox::QWidgetComBox(const QStringList &texts, QWidget *parent) : QWidget(parent)
{
    m_box = new QComboBox();
    m_box->addItems(texts);

    QHBoxLayout *hLayout = new QHBoxLayout();       //创建布局
    hLayout->addWidget(m_box);                      //添加checkbox
    hLayout->setMargin(0);                          //设置边缘距离 否则会很难看
    hLayout->setAlignment(m_box, Qt::AlignCenter);  //居中
    this->setLayout(hLayout);                       //设置widget的布局
}

QWidgetComBox::~QWidgetComBox()
{
    delete m_box;
    m_box = nullptr;
}

void QWidgetComBox::setCurrentText(QString s)
{
    m_box->setCurrentText(s);
}

QString QWidgetComBox::currentText()
{
    return m_box->currentText();
}
