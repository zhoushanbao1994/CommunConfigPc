#ifndef QWIDGETCHECKBOX_H
#define QWIDGETCHECKBOX_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>

class QWidgetCheckBox : public QWidget
{
    Q_OBJECT
public:
    explicit QWidgetCheckBox(QWidget *parent = nullptr);
    ~QWidgetCheckBox();
    Qt::CheckState checkState();
    void setCheckState(Qt::CheckState s);

signals:

private:
    QCheckBox *m_box;
};

#endif // QWIDGETCHECKBOX_H
