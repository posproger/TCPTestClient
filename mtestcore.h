#ifndef MTESTCORE_H
#define MTESTCORE_H

#include <QObject>
#include <QThread>
#include "mtestthread.h"

class MTestCore : public QThread
{
    Q_OBJECT
public:
    MTestCore(QObject * parent=0);
    ~MTestCore();

signals:
    void checkStatistics(void);

protected:
    void run();

public slots:

private:
    MTestThread * m_thread;

};

#endif // MTESTCORE_H
