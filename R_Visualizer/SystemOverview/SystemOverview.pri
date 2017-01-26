#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T01:52:38
#
#-------------------------------------------------
DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD

SOURCES += $$PWD//systemoverview.cpp \
    $$PWD/sysoverviewgraphicsview.cpp \
    $$PWD/isysovrvelement.cpp

HEADERS  += $$PWD//systemoverview.h \
    $$PWD/sysoverviewgraphicsview.h \
    $$PWD/isysovrvelement.h

FORMS    += $$PWD//systemoverview.ui

include(SysOvrvObj/SysOvrvObj.pri)
include(SysOvrvTrigger/SysOvrvTrigger.pri)
