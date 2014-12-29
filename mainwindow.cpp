#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");

    m_core = new MTestCore();
    m_core->moveToThread(m_core);
    //connect(m_core,SIGNAL(),this,SLOT());
    connect(ui->pbStat,SIGNAL(clicked()),m_core,SIGNAL(checkStatistics()));
    m_core->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
