#ifndef QWIDGETCOMBOX_H
#define QWIDGETCOMBOX_H

#include <QObject>
#include <QWidget>
#include <QComboBox>

class QWidgetComBox : public QWidget
{
    Q_OBJECT
public:
    explicit QWidgetComBox(const QStringList &texts, QWidget *parent = nullptr);
    ~QWidgetComBox();
    void setCurrentText(QString s);
    QString currentText();

signals:

private:
    QComboBox *m_box;
};

#endif // QWIDGETCOMBOX_H
