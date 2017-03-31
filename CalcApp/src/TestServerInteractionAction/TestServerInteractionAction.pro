include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = TestServerInteractionAction
TEMPLATE = lib
CONFIG += plugin

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES +=

HEADERS +=
DISTFILES += TestServerInteractionAction.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
