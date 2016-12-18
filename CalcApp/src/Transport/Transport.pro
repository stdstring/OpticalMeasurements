#-------------------------------------------------
#
# Project created by QtCreator 2016-12-18T10:24:18
#
#-------------------------------------------------

QT += core

TARGET = Transport
TEMPLATE = lib
CONFIG += plugin

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES +=

HEADERS +=
DISTFILES += Transport.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
