include( ../../common.pri )
include( ../../lib.pri )

QT += core network

TARGET = TestServerCore
TEMPLATE = lib
CONFIG += staticlib

SOURCES += TestServer.cpp \
           TestServerRunner.cpp

HEADERS += TestServerConfig.h \
           TestServer.h \
           TestServerRunner.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
