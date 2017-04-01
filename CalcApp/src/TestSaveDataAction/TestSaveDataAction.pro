include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = TestSaveDataAction$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += plugin

DEFINES += TEST_SAVE_DATA_ACTION_LIBRARY

LIBS += -lCommon

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES += TestSaveDataAction.cpp \
           TestSaveDataActionFactory.cpp

HEADERS += TestSaveDataAction.h \
           TestSaveDataActionFactory.h

DISTFILES += TestSaveDataAction.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
