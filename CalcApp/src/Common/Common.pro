include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = Common
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS += ../../include/Common/ITransport.h \
           ../../include/Common/ITransportFactory.h \
           ../../include/Common/Message.h \
           ../../include/Common/TransportConfig.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
