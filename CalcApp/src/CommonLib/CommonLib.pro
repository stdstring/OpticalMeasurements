QT += widgets

TARGET = CommonLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS += ITransport.h \
           ICalculator.h \
           MessageType.h \
           Message.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
