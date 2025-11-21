#include "qwidgetcheckbox.h"
#include <QHBoxLayout>

QWidgetCheckBox::QWidgetCheckBox(QWidget *parent) : QWidget(parent)
{
    m_box = new QCheckBox();

    QHBoxLayout *hLayout = new QHBoxLayout();       //创建布局
    hLayout->addWidget(m_box);                      //添加checkbox
    hLayout->setMargin(0);                          //设置边缘距离 否则会很难看
    hLayout->setAlignment(m_box, Qt::AlignCenter);  //居中
    this->setLayout(hLayout);                       //设置widget的布局
}

QWidgetCheckBox::~QWidgetCheckBox()
{
    delete  m_box;
    m_box = nullptr;
}

Qt::CheckState QWidgetCheckBox::checkState()
{
    return m_box->checkState();
}

void QWidgetCheckBox::setCheckState(Qt::CheckState s)
{
    m_box->setCheckState(s);
}
