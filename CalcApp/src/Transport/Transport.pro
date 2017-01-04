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
CONFIG += plugin C++11

DEFINES += TRANSPORT_LIBRARY

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES += Transport.cpp \
           TransportFactory.cpp \
           MessageInfoFactory.cpp \
           MessageValidator.cpp \
           SimpleMessageCheckStrategy.cpp \
           TransportLowLevel.cpp

HEADERS += ../../include/ITransport.h \
           ../../include/ITransportFactory.h \
           ../../include/Message.h \
           ../../include/MessageType.h \
           Transport.h \
           TransportFactory.h \
           MessageInfo.h \
           MessageInfoFactory.h \
           MessageValidator.h \
           IMessageCheckStrategy.h \
           SimpleMessageCheckStrategy.h \
           TransportLowLevel.h \
           TransportLowLevelBase.h

DISTFILES += Transport.json

win32 {
    QMAKE_TARGET_PRODUCT = Transport
    QMAKE_TARGET_DESCRIPTION = Transport plugin library
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
