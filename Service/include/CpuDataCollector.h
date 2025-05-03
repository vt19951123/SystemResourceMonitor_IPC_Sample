#ifndef CPUDATACOLLECTOR_H
#define CPUDATACOLLECTOR_H

#include <QObject>

class CpuDataCollector : public QObject
{
    Q_OBJECT
public:
    explicit CpuDataCollector(QObject *parent = nullptr);

signals:
};

#endif // CPUDATACOLLECTOR_H
