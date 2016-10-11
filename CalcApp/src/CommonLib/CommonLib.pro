QT       -= gui

TARGET = CommonLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS += \
    ITransport.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
