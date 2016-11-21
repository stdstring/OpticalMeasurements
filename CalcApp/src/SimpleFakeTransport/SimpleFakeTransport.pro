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

SOURCES += SimpleFakeTransport.cpp

HEADERS += ..\CommonLib\ITransport.h \
           SimpleFakeTransport.h

DISTFILES += SimpleFakeTransport.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
