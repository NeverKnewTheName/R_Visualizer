#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T01:53:25
#
#-------------------------------------------------
DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/SendMessages.cpp \
#    $$PWD/src/sendmessages.cpp \
#    $$PWD/src/sendmsgmodel.cpp \
    $$PWD/src/SendMessagesWidget.cpp \
    $$PWD/src/SendMsgSingleWidget.cpp \
    $$PWD/src/SendMsgPackageWidget.cpp

HEADERS  += \
    $$PWD/inc/ISendMessages.h \
    $$PWD/inc/SendMessages.h \
#    $$PWD/inc/sendmessages.h \
#    $$PWD/inc/sendmsgmodel.h \
    $$PWD/inc/SendMessagesWidget.h \
    $$PWD/inc/SendMsgSingleWidget.h \
    $$PWD/inc/SendMsgPackageWidget.h

FORMS    += \
#    $$PWD/ui/sendmessages.ui \
    $$PWD/ui/sendmessageswidget.ui \
    $$PWD/ui/sendmsgsinglewidget.ui \
    $$PWD/ui/sendmsgpackagewidget.ui
