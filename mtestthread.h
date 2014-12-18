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

private:
    QTcpSocket * m_socket;
    QLClientNetManager * m_netManager;
    QTimer * m_timer;

};

#endif // MTESTTHREAD_H
