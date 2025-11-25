#ifndef JSONGENERAT_H
#define JSONGENERAT_H

#include <QObject>

class JsonGenerat : public QObject
{
    Q_OBJECT
public:
    explicit JsonGenerat(QObject *parent = nullptr);

signals:
};

#endif // JSONGENERAT_H
