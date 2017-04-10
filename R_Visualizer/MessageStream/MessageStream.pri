DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/MessageStream.cpp \
#    $$PWD/src/msgstream.cpp \
#    $$PWD/src/msgstreammodel.cpp \
#    $$PWD/src/messagestream.cpp \
    $$PWD/src/MessageStreamWidget.cpp \
    $$PWD/src/MsgStreamStore.cpp \
    $$PWD/src/MsgStreamModel.cpp \

HEADERS  += \
    $$PWD/inc/IMessageStream.h \
    $$PWD/inc/MessageStream.h \
#    $$PWD/inc/msgstream.h \
#    $$PWD/inc/msgstreammodel.h \
#    $$PWD/inc/messagestream.h \
    $$PWD/inc/MessageStreamWidget.h \
    $$PWD/inc/IMsgStreamStore.h \
    $$PWD/inc/MsgStreamStore.h \
    $$PWD/inc/IMsgStreamModel.h \
    $$PWD/inc/MsgStreamModel.h \


FORMS    += \
#    $$PWD/ui/msgstream.ui \
    $$PWD/ui/messagestream.ui \
    $$PWD/ui/messagestreamwidget.ui

