include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = TestSaveDataAction
TEMPLATE = lib
CONFIG += plugin

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES +=

HEADERS +=

DISTFILES += TestSaveDataAction.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
