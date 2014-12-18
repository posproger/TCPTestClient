#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T22:38:05
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCPTestClt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mtestcore.cpp \
    mtestthread.cpp

HEADERS  += mainwindow.h \
    mtestcore.h \
    mtestthread.h


ATPATH = "../AT_Shared"

SOURCES += $$ATPATH/qlclientnetmanager.cpp

HEADERS  += $$ATPATH/at_shared.h \
    $$ATPATH/qlclientnetmanager.h

INCLUDEPATH += ../AT_Shared


FORMS    += mainwindow.ui
