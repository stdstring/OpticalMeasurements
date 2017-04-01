include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = TestInteractionAction$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += plugin

DEFINES += TEST_INTERACTION_ACTION_LIBRARY

LIBS += -lCommon

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES += TestInteractionAction.cpp \
           TestInteractionActionFactory.cpp

HEADERS += TestInteractionAction.h \
           TestInteractionActionFactory.h

DISTFILES += TestInteractionAction.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
