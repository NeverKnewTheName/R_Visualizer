DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/SysOverviewObjectColorTrigger.cpp \
    $$PWD/src/SysOvrvObjColorTriggerDialog.cpp

HEADERS  += \
    $$PWD/inc/ISysOverviewObjectTrigger.h \
    $$PWD/inc/SysOverviewObjectColorTrigger.h \
    $$PWD/inc/SysOvrvObjColorTriggerDialog.h

FORMS    += \
    $$PWD/ui/sysovrvobjcolortriggerdialog.ui

include(SysOverviewObjectTriggerEvaluator/SysOverviewObjectTriggerEvaluator.pri)
include(SysOverviewLabelTrigger/SysOverviewLabelTrigger.pri)
