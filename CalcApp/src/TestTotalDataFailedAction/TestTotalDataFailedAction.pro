include( ../../common.pri )
include( ../../lib.pri )

QT       += core

TARGET = TestTotalDataFailedAction$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += plugin

DEFINES += TEST_TOTAL_DATA_FAILED_ACTION_LIBRARY

LIBS += -lCommon

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += TestTotalDataFailedAction.cpp \
           TestTotalDataFailedActionFactory.cpp

HEADERS += ../../include/Common/Context.h \
           ../../include/Common/IAction.h \
           ../../include/Common/IActionFactory.h \
           ../../include/Common/IComponentInfo.h \
           ../../include/Common/MainConfig.h \
           TestTotalDataFailedAction.h \
           TestTotalDataFailedActionFactory.h

DISTFILES += TestTotalDataFailedAction.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
