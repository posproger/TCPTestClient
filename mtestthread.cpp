#include "mtestthread.h"
#include "at_shared.h"
#include <QUrl>

MTestThread::MTestThread(QObject *parent) : QThread(parent){
    m_netManager = new QLClientNetManager(0, 0);
    connect(m_netManager,SIGNAL(newBinaryMessageReceived(QByteArray)),this,SLOT(newBinMsgFromServer(QByteArray)));
    connect(m_netManager,SIGNAL(socketDisconnected()),this,SLOT(socketDisconnected()));
    connect(m_netManager,SIGNAL(socketConnected()),this,SLOT(socketConnected()));

    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    m_timer->setInterval(5000);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(timeoutSlot()));
}

MTestThread::~MTestThread() {
    deleteLater();
    quit();
    wait();
}

void MTestThread::run() {
    QTcpSocket * m_tcpSocket = new QTcpSocket();
    m_netManager->setTCPSocket(m_tcpSocket);
    QUrl m_url;
    m_url.setHost("localhost");
    m_url.setPort(8085-1);
    m_netManager->makeConnect(m_url);
    exec();
}

void MTestThread::newBinMsgFromServer(QByteArray in) {
    QString zz;
    zz.append(in);
    if ( in.size()!=zz.size() ) {
        qlDebug() << "Size incorrect!" << in.size() << zz.size();
    }
    m_timer->start();
}

void MTestThread::socketDisconnected() {
    ;
}

void MTestThread::socketConnected() {
    qlDebug();
    m_timer->start();
}

void MTestThread::timeoutSlot() {
    QByteArray zz;
    for ( int i=0; i<60000; ++i ) {
        zz.append("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\r\n");
    }
    m_netManager->sendBinaryMessage(zz);
}
