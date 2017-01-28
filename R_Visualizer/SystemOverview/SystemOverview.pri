#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T01:52:38
#
#-------------------------------------------------
DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/systemoverview.cpp \
    $$PWD/src/sysoverviewgraphicsview.cpp \
    $$PWD/src/isysovrvelement.cpp

HEADERS  += \
    $$PWD/inc/systemoverview.h \
    $$PWD/inc/sysoverviewgraphicsview.h \
    $$PWD/inc/isysovrvelement.h

FORMS    += \
    $$PWD/ui/systemoverview.ui

include(SysOvrvObj/SysOvrvObj.pri)
include(SysOvrvTrigger/SysOvrvTrigger.pri)
