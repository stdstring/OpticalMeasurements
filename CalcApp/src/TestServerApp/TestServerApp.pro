include( ../../common.pri )

QT += core
QT -= gui

TARGET = TestServerApp
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lCommon

SOURCES += main.cpp \
           ConfigReader.cpp

HEADERS += ConfigReader.h
