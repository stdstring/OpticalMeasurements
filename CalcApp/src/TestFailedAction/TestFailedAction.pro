include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = TestFailedAction$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += plugin

DEFINES += TEST_FAILED_ACTION_LIBRARY

LIBS += -lCommon

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES += TestFailedAction.cpp \
           TestFailedActionFactory.cpp

HEADERS += ../../include/Common/Context.h \
           ../../include/Common/IAction.h \
           ../../include/Common/IActionFactory.h \
           ../../include/Common/IComponentInfo.h \
           ../../include/Common/MainConfig.h \
           TestFailedAction.h \
           TestFailedActionFactory.h

DISTFILES += TestFailedAction.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
