#-------------------------------------------------
#
# Project created by QtCreator 2016-12-18T10:24:18
#
#-------------------------------------------------

include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = Transport$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += plugin

DEFINES += TRANSPORT_LIBRARY

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES += \

HEADERS += ../../include/ITransport.h \
           ../../include/ITransportFactory.h \
           ../../include/Message.h \
           ../../include/MessageType.h

DISTFILES += Transport.json

win32 {
    QMAKE_TARGET_PRODUCT = Transport
    QMAKE_TARGET_DESCRIPTION = Transport plugin library
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
