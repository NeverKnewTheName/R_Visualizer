DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/SystemOverviewObject.cpp \
    $$PWD/src/SysOverviewObjectDialog.cpp \
    $$PWD/src/SysOverviewTextLabel.cpp \

HEADERS  += \
    $$PWD/inc/ISystemOverviewObject.h \
    $$PWD/inc/SystemOverviewObject.h \
    $$PWD/inc/SysOverviewTextLabel.h \
    $$PWD/inc/SysOverviewObjectDialog.h \

FORMS    += \
    $$PWD/ui/sysoverviewobjectdialog.ui \

include(SysOverviewObjectManager/SysOverviewObjectManager.pri)
include(SysOverviewObjectResizeManager/SysOverviewObjectResizeManager.pri)
