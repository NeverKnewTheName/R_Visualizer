#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T01:53:25
#
#-------------------------------------------------
DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/Msg.cpp \
    # $$PWD/src/msgtableview.cpp \
    # $$PWD/src/msgdatawidget.cpp \
    $$PWD/src/TimestampedMsg.cpp \

HEADERS  += \
    $$PWD/inc/MsgFieldType.h \
    # $$PWD/inc/IMsgFieldType.h \
    $$PWD/inc/MsgIDType.h \
    $$PWD/inc/MsgCodeType.h \
    $$PWD/inc/MsgDataType.h \
    $$PWD/inc/MessageTypeIdentifier.h \
    $$PWD/inc/IMsg.h \
    $$PWD/inc/ITimestamp.h \
    $$PWD/inc/ITimestampedMsg.h \
    $$PWD/inc/TimestampedMsg.h \
    $$PWD/inc/Msg.h \
    $$PWD/inc/IPrettyMsg.h \
    $$PWD/inc/PrettyMsg.h \
    $$PWD/inc/PrettyTimestampedMsg.h \

FORMS    += \
    $$PWD/ui/msgdisplaywidget.ui \
    $$PWD/ui/msgdatawidget.ui \

include(Widgets/MsgWidgets.pri)
include(Delegates/MsgDelegates.pri)
