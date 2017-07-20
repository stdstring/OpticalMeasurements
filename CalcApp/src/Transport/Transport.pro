include(../../common.pri)
include(../../lib.pri)

QT += core network

TARGET = Transport$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += plugin

DEFINES += TRANSPORT_LIBRARY

LIBS += -lCommon

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES += LowLevel/TransportLowLevel.cpp \
           LowLevel/TcpTransport.cpp \
           LowLevel/UdpTransport.cpp \
           Transport.cpp \
           TransportFactory.cpp \
           MessageInfoFactory.cpp \
           SimpleMessageCheckStrategy.cpp \
           DelayedMessagesProcessor.cpp \
           MessageValidation.cpp

HEADERS += ../../include/Common/ITransport.h \
           ../../include/Common/ITransportFactory.h \
           ../../include/Common/Message.h \
           ../../include/Common/TransportConfig.h \
           ../../include/Common/TransportSerialization.h \
           LowLevel/TransportLowLevel.h \
           LowLevel/TcpTransport.h \
           LowLevel/UdpTransport.h \
           Transport.h \
           TransportFactory.h \
           MessageInfo.h \
           MessageInfoFactory.h \
           IMessageCheckStrategy.h \
           SimpleMessageCheckStrategy.h \
           TransportConfig.h \
           DelayedMessagesProcessor.h \
           MessageValidation.h

DISTFILES += Transport.json

win32 {
    QMAKE_TARGET_PRODUCT = Transport
    QMAKE_TARGET_DESCRIPTION = Transport plugin library
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
