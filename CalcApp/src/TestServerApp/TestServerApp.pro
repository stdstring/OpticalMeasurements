include( ../../common.pri )
include( ../../app.pri )

QT += core network

TARGET = TestServerApp
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lTestServerCore -lCommon

SOURCES += main.cpp \
           ConfigReader.cpp \
           CommandLineDefs.cpp

HEADERS += ConfigReader.h \
           CommandLineDefs.h

DISTFILES += TestServer.conf \
             TestServerWithBadData.conf \
             TestServerSimpleCylinderData.conf
