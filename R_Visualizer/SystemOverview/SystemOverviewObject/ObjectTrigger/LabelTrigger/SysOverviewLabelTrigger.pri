DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/SysOverviewLabelTextChangeTrigger.cpp \
    $$PWD/src/SysOverviewLabelTextChangeTriggerDialog.cpp \
    $$PWD/src/SysOverviewLabelTextEvaluatorTrigger.cpp \
    $$PWD/src/SysOverviewLabelTextEvaluatorTriggerDialog.cpp

HEADERS  += \
    $$PWD/inc/ISysOverviewLabelTrigger.h \
    $$PWD/inc/SysOverviewLabelTextChangeTrigger.h \
    $$PWD/inc/SysOverviewLabelTextChangeTriggerDialog.h \
    $$PWD/inc/SysOverviewLabelTextEvaluatorTrigger.h \
    $$PWD/inc/SysOverviewLabelTextEvaluatorTriggerDialog.h

FORMS    += \
    $$PWD/ui/sysoverviewlabeltextchangetriggerdialog.ui \
    $$PWD/ui/sysoverviewlabeltextevaluatortriggerdialog.ui
