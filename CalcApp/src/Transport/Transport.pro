include( ../../common.pri )
#include( ../../lib.pri )

QT += core network

TARGET = Transport$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += plugin

DEFINES += TRANSPORT_LIBRARY

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES += LowLevel/TransportLowLevel.cpp \
           LowLevel/TcpTransport.cpp \
           LowLevel/UdpTransport.cpp \
           Transport.cpp \
           TransportFactory.cpp \
           MessageInfoFactory.cpp \
           MessageValidator.cpp \
           SimpleMessageCheckStrategy.cpp \
           DelayedMessagesProcessor.cpp

HEADERS += ../../include/ITransport.h \
           ../../include/ITransportFactory.h \
           ../../include/Message.h \
           LowLevel/TransportLowLevel.h \
           LowLevel/TcpTransport.h \
           LowLevel/UdpTransport.h \
           Transport.h \
           TransportFactory.h \
           MessageInfo.h \
           MessageInfoFactory.h \
           MessageValidator.h \
           IMessageCheckStrategy.h \
           SimpleMessageCheckStrategy.h \
           TransportConfig.h \
           DelayedMessagesProcessor.h

DISTFILES += Transport.json

win32 {
    QMAKE_TARGET_PRODUCT = Transport
    QMAKE_TARGET_DESCRIPTION = Transport plugin library
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
