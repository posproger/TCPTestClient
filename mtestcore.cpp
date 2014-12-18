#include "mtestcore.h"
#include "at_shared.h"

MTestCore::MTestCore(QObject * parent) : QThread(parent) {
    m_thread = new MTestThread();
    m_thread->moveToThread(m_thread);
}

MTestCore::~MTestCore() {
    if ( m_thread ) m_thread->deleteLater();
    deleteLater();
    quit();
    wait();
}

void MTestCore::run() {
    qlDebug() << "Core running" << this << m_thread;
    m_thread->start();
    exec();
}
