include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = TestActionB$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += plugin

DEFINES += TEST_ACTION_B_LIBRARY

LIBS += -lCommon

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES += TestActionB.cpp \
           TestActionBFactory.cpp

HEADERS += ../../include/Common/Context.h \
           ../../include/Common/IAction.h \
           ../../include/Common/IActionFactory.h \
           ../../include/Common/IComponentInfo.h \
           ../../include/Common/MainConfig.h \
           TestActionB.h \
           TestActionBFactory.h

DISTFILES += TestActionB.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
