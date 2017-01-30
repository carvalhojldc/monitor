#-------------------------------------------------
#
# Project created by QtCreator 2016-10-07T17:36:59
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ssm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    Linux/cpu.cpp \
    Linux/meminfo.cpp \
    Linux/ProcessData.cpp \
    Linux/Processes.cpp
    Linux/Processes.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    Linux/cpu.h \
    Linux/meminfo.h \
    Linux/Process.h \
    Linux/ProcessData.h \
    Linux/Processes.h

FORMS    += mainwindow.ui
