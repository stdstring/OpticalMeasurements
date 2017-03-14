include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = TestActionA$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += plugin

DEFINES += TEST_ACTION_A_LIBRARY

LIBS += -lCommon

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES += TestActionA.cpp \
           TestActionAFactory.cpp

HEADERS += ../../include/Common/Context.h \
           ../../include/Common/IAction.h \
           ../../include/Common/IActionFactory.h \
           ../../include/Common/IComponentInfo.h \
           ../../include/Common/MainConfig.h \
           TestActionA.h \
           TestActionAFactory.h

DISTFILES += TestActionA.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
