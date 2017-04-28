DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/AbstractMsgFieldLineEdit.cpp
    $$PWD/src/MsgIDLineEdit.cpp \
    $$PWD/src/MsgCodeLineEdit.cpp \
    $$PWD/src/MsgDataLineEdit.cpp \

HEADERS  += \
    $$PWD/inc/AbstractMsgFieldLineEdit.h
    $$PWD/inc/MsgIDLineEdit.h \
    $$PWD/inc/MsgCodeLineEdit.h \
    $$PWD/inc/MsgDataLineEdit.h \

FORMS    += \
    $$PWD/ui/msgidlineedit.ui \
    $$PWD/ui/msgcodelineedit.ui \
    $$PWD/ui/msgdatalineedit.ui

