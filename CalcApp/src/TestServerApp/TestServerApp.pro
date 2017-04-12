include( ../../common.pri )
include( ../../app.pri )

QT += core network
QT -= gui

TARGET = TestServerApp
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lTestServerCore -lCommon

SOURCES += main.cpp \
           ConfigReader.cpp

HEADERS += ConfigReader.h

DISTFILES += TestServer.config
