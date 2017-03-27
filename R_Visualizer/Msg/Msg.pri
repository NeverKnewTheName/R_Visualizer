#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T01:53:25
#
#-------------------------------------------------
DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/Msg.cpp \
    $$PWD/src/msgtableview.cpp \
    $$PWD/src/msgdatawidget.cpp \
    $$PWD/src/Prettymsg.cpp \

HEADERS  += \
    $$PWD/inc/MsgFieldType.h \
    $$PWD/inc/IMsgFieldType.h \
    $$PWD/inc/MsgIDType.h \
    $$PWD/inc/MsgCodeType.h \
    $$PWD/inc/MsgDataType.h \
    $$PWD/inc/IMsgDataFormatter.h \ #Should be in MessageConfig
    $$PWD/inc/IMsg.h \
    $$PWD/inc/ITimestampedMsg.h \
    $$PWD/inc/TimestampedMsg.h \
    $$PWD/inc/Msg.h \
    $$PWD/inc/IPrettyMsg.h \
    $$PWD/inc/PrettyMsg.h \

FORMS    += \
    $$PWD/ui/msgdisplaywidget.ui \
    $$PWD/ui/msgdatawidget.ui
