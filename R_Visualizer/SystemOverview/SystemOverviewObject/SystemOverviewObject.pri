DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/SystemOverviewObject.cpp \
    $$PWD/src/SysOverviewObjectShapeManager.cpp \
    $$PWD/src/SysOverviewObjectImageManager.cpp \
    $$PWD/src/SysOverviewObjectResizeManager.cpp \

HEADERS  += \
    $$PWD/inc/ISystemOverviewObject.h \
    $$PWD/inc/SystemOverviewObject.h \
    $$PWD/inc/ISysOverviewObjectManager.h \
    $$PWD/inc/SysOverviewObjectShapeManager.h \
    $$PWD/inc/SysOverviewObjectImageManager.h \
    $$PWD/inc/ISysOverviewObjectResizeManager.h \
    $$PWD/inc/SysOverviewObjectResizeManager.h \

FORMS    += \
