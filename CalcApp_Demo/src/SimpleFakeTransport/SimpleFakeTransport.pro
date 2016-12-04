#-------------------------------------------------
#
# Project created by QtCreator 2016-11-13T21:01:25
#
#-------------------------------------------------

QT       += core

TARGET = SimpleFakeTransport
TEMPLATE = lib
CONFIG += plugin c++11

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES += SimpleFakeTransport.cpp \
           SimpleFakeTransportFactory.cpp

HEADERS += ..\CommonLib\ITransport.h \
           ..\CommonLib\ITransportFactory.h \
           ..\CommonLib\Message.h \
           ..\CommonLib\MessageType.h \
           ..\CommonLib\TransportConfig.h \
           SimpleFakeTransport.h \
           SimpleFakeTransportFactory.h

DISTFILES += SimpleFakeTransportFactory.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
