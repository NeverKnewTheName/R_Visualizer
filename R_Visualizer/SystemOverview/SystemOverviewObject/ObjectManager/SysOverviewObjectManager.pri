DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/SysOverviewObjectShapeManager.cpp \
    $$PWD/src/SysOverviewObjectImageManager.cpp \
    $$PWD/src/SysOverviewObjectColorManager.cpp \
    $$PWD/src/SysOverviewObjectShapeManagerWidget.cpp \
    $$PWD/src/SysOverviewObjectManagerWidget.cpp \
    $$PWD/src/ISysOverviewObjectManagerSubWidget.cpp \
    $$PWD/src/SysOverviewObjectImageManagerWidget.cpp

HEADERS  += \
    $$PWD/inc/ISysOverviewObjectManager.h \
    $$PWD/inc/SysOverviewObjectShapeManager.h \
    $$PWD/inc/SysOverviewObjectImageManager.h \
    $$PWD/inc/ISysOverviewObjectColorManager.h \
    $$PWD/inc/SysOverviewObjectColorManager.h \
    $$PWD/inc/SysOverviewObjectShapeManagerWidget.h \
    $$PWD/inc/SysOverviewObjectManagerWidget.h \
    $$PWD/inc/ISysOverviewObjectManagerSubWidget.h \
    $$PWD/inc/SysOverviewObjectImageManagerWidget.h

FORMS    += \
    $$PWD/ui/sysoverviewobjectshapemanagerwidget.ui \
    $$PWD/ui/sysoverviewobjectmanagerwidget.ui \
    $$PWD/ui/sysoverviewobjectimagemanagerwidget.ui

