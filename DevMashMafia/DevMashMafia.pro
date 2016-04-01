#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T21:35:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DevMashMafia
TEMPLATE = app

CONFIG+=no_keywords
CONFIG+=c++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/sioclient/build/include
DEPENDPATH += $$PWD/sioclient/build/lib

LIBS += -L$$PWD/sioclient/build/lib/Release/ -lsioclient

LIBS += -L$$PWD/sioclient/build/lib/Release/ -lboost_random

LIBS += -L$$PWD/sioclient/build/lib/Release/ -lboost_system

LIBS += -L$$PWD/sioclient/build/lib/Release/ -lboost_date_time
