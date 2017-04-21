#-------------------------------------------------
#
# Project created by QtCreator 2016-05-31T23:57:59
#
#-------------------------------------------------
DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/MessageConfig.cpp \
    $$PWD/src/MessageConfigNotifier.cpp \
    $$PWD/src/MessageConfigWidget.cpp \

HEADERS  += \
    $$PWD/inc/IMessageConfig.h \
    $$PWD/inc/MessageConfig.h \
    $$PWD/inc/MessageConfigNotifier.h \
    $$PWD/inc/MessageConfigWidget.h \
    $$PWD/inc/IPlainTextAliasMapping.h \
    $$PWD/inc/IColorRepresentationMapping.h \
    $$PWD/inc/IMsgMapping.h \

FORMS    += \
    $$PWD/ui/messageconfig.ui \
    $$PWD/ui/messageconfigwidget.ui \

include(MsgIDMapping/MsgIDMapping.pri)
include(MsgCodeMapping/MsgCodeMapping.pri)
include(MsgDataMapping/MsgDataMapping.pri)
