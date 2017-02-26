#-------------------------------------------------
#
# Project created by QtCreator 2017-02-26T09:54:25
#
#-------------------------------------------------

QT       -= gui

TARGET = TestServerCore
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS +=
unix {
    target.path = /usr/lib
    INSTALLS += target
}
