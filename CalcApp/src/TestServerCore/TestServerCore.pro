include( ../../common.pri )
include( ../../lib.pri )

QT += core network

TARGET = TestServerCore
TEMPLATE = lib
CONFIG += staticlib

LIBS += -lCommon

INCLUDEPATH += ../../include/TestServerCore

SOURCES += TestServer.cpp \
           TestServerRunner.cpp

HEADERS += ../../include/TestServerCore/TestServerConfig.h \
           ../../include/TestServerCore/TestServer.h \
           ../../include/TestServerCore/TestServerRunner.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
