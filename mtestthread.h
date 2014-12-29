#ifndef MTESTTHREAD_H
#define MTESTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QByteArray>
#include <QTimer>
#include "qlclientnetmanager.h"

class MTestThread : public QThread
{
    Q_OBJECT
public:
    MTestThread(QObject * parent=0);
    ~MTestThread();

signals:

protected:
    void run();

public slots:
    void newBinMsgFromServer(QByteArray in);
    void socketDisconnected();
    void socketConnected();
    void timeoutSlot();
    void resendSlot();
    void binaryMessageSent(quint32 packetN);
    void checkStatistics(void);

private:
    QTcpSocket * m_socket;
    QLClientNetManager * m_netManager;
    QTimer * m_timer;
    QTimer * m_timerLoose;

    int m_count;
    int m_loose;
    int m_err;

    quint32 m_packetN;
};

#endif // MTESTTHREAD_H
