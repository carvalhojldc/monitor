#-------------------------------------------------
#
# Project created by QtCreator 2016-10-07T17:36:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = monitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cpu.cpp

HEADERS  += mainwindow.h \
    cpu.h

FORMS    += mainwindow.ui
