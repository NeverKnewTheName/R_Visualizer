#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T01:52:38
#
#-------------------------------------------------
DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/SystemOverview.cpp \
    $$PWD/src/SystemOverviewNotifier.cpp \
    # $$PWD/src/systemoverview.cpp \
    $$PWD/src/sysoverviewgraphicsview.cpp \
    $$PWD/src/isysovrvelement.cpp \
    $$PWD/src/SystemOverviewWidget.cpp \

HEADERS  += \
    $$PWD/inc/ISystemOverview.h \
    $$PWD/inc/SystemOverview.h \
    $$PWD/inc/SystemOverviewNotifier.h \
    # $$PWD/inc/systemoverview.h \
    $$PWD/inc/sysoverviewgraphicsview.h \
    $$PWD/inc/isysovrvelement.h \
    $$PWD/inc/SystemOverviewWidget.h \

FORMS    += \
    $$PWD/ui/systemoverview.ui \
    $$PWD/ui/systemoverviewwidget.ui

include(SysOvrvObj/SysOvrvObj.pri)
include(SysOvrvTrigger/SysOvrvTrigger.pri)
