#include "mtestthread.h"
#include "at_shared.h"
#include <QUrl>

MTestThread::MTestThread(QObject *parent) : QThread(parent){
    m_netManager = new QLClientNetManager(0, 0);
    connect(m_netManager,SIGNAL(newBinaryMessageReceived(QByteArray)),this,SLOT(newBinMsgFromServer(QByteArray)));
    connect(m_netManager,SIGNAL(socketDisconnected()),this,SLOT(socketDisconnected()));
    connect(m_netManager,SIGNAL(socketConnected()),this,SLOT(socketConnected()));
    connect(m_netManager,SIGNAL(binaryMessageSent(quint32)),this,SLOT(binaryMessageSent(quint32)));

    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    m_timer->setInterval(2000);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(timeoutSlot()));

    m_timerLoose = new QTimer(this);
    m_timerLoose->setSingleShot(true);
    m_timerLoose->setInterval(10000);
    connect(m_timerLoose,SIGNAL(timeout()),this,SLOT(resendSlot()));

    m_err = 0;
    m_loose = 0;
    m_count = 0;

    m_packetN = 1;
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
        ++m_err;
        qlDebug() << "Size incorrect!" << in.size() << zz.size() << m_err << m_loose;
    }
    //m_timerLoose->stop();
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
    if ( m_packetN<900001 ) {
        m_netManager->sendBinaryMessage(zz, m_packetN++);
    } else {
        qlDebug() << "Total:" << m_count << "Error:" << m_err << "Lost:" << m_loose << "Cur.Packet:" << m_packetN;
        qlDebug() << "Test stop...";
    }
    //m_timerLoose->start();

    ++m_count;
    if ( m_count%10==0 ) qlDebug() << "Total:" << m_count << "Error:" << m_err << "Lost:" << m_loose << "Cur.Packet:" << m_packetN;
}

void MTestThread::resendSlot() {
    ++m_loose;
    m_netManager->tryRefreshTcp();
    timeoutSlot();
}

void MTestThread::binaryMessageSent(quint32 packetN) {
    qlDebug() << packetN;
}

