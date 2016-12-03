#-------------------------------------------------
#
# Project created by QtCreator 2016-10-15T22:26:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainApp
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
           MainWindow.cpp \
           SimpleConfigFactory.cpp

HEADERS  += MainWindow.h \
            MainAppConfig.h \
            SimpleConfigFactory.h

FORMS    += MainWindow.ui
