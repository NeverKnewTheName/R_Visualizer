#-------------------------------------------------
#
# Project created by QtCreator 2016-05-31T23:57:59
#
#-------------------------------------------------
DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/MessageFilter.cpp \
    $$PWD/src/MessageFilterNotifier.cpp \
    $$PWD/src/MessageFilterWidget.cpp \

HEADERS  += \
    $$PWD/inc/IMessageFilter.h \
    $$PWD/inc/MessageFilterNotifier.h \
    $$PWD/inc/MessageFilter.h \
    $$PWD/inc/MessageFilterWidget.h \
    $$PWD/inc/IFilter.h \
    $$PWD/inc/IMsgFilter.h \
    $$PWD/inc/ITimestampedMsgFilter.h \

FORMS    += \
    $$PWD/ui/messagefilterwidget.ui \

include(MsgIDFilter/MsgIDFilter.pri)
include(MsgCodeFilter/MsgCodeFilter.pri)
include(MsgTimestampFilter/MsgTimestampFilter.pri)
