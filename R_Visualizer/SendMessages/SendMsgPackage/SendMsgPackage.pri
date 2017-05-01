DEPENDPATH += $$PWD/inc
INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$PWD/src/SendMsgPackage.cpp \
    $$PWD/src/SendMsgPackageStore.cpp \
    $$PWD/src/SendMsgPackageModel.cpp \
    $$PWD/src/SendMsgPackageWidget.cpp \
    $$PWD/src/SendMsgPackageAddDialog.cpp

HEADERS  += \
    $$PWD/inc/ISendMsgPackage.h \
    $$PWD/inc/ISendMsgPackageStore.h \
    $$PWD/inc/ISendMsgPackageModel.h \
    $$PWD/inc/SendMsgPackage.h \
    $$PWD/inc/SendMsgPackageStore.h \
    $$PWD/inc/SendMsgPackageModel.h \
    $$PWD/inc/SendMsgPackageWidget.h \
    $$PWD/inc/SendMsgPackageAddDialog.h

FORMS    += \
    $$PWD/ui/sendmsgpackagewidget.ui \
    $$PWD/ui/sendmsgpackageadddialog.ui
