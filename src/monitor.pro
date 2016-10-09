#-------------------------------------------------
#
# Project created by QtCreator 2016-10-07T17:36:59
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = monitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cpu.cpp \
    meminfo.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    cpu.h \
    meminfo.h \
    qcustomplot.h

FORMS    += mainwindow.ui
