QT += widgets

TARGET = CommonLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS += \
    ITransport.h \
    ICalculator.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
