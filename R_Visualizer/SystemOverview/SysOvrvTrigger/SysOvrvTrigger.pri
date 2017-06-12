#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T01:52:38
#
#-------------------------------------------------
DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/sysovrvtrigger.cpp \
    $$PWD/src/sysovrvobjtriggerdialog.cpp \
    $$PWD/src/sysovrvtriggermodel.cpp \
    $$PWD/src/sysovrvtriggereditorwidget.cpp \
    $$PWD/src/evaluatortablemodel.cpp

HEADERS  += \
    $$PWD/inc/sysovrvtrigger.h \
    $$PWD/inc/sysovrvobjtriggerdialog.h \
    $$PWD/inc/sysovrvtriggermodel.h \
    $$PWD/inc/sysovrvtriggereditorwidget.h \
    $$PWD/inc/evaluatortablemodel.h

FORMS    += \
    $$PWD/ui/sysovrvobjtriggerdialog.ui \
    $$PWD/ui/sysovrvtriggereditorwidget.ui

include(SysOvrvTriggerEvaluator/SysOvrvTriggerEvaluator.pri)
