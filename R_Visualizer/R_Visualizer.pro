#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T14:29:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = R_Visualizer
TEMPLATE = app


INCLUDEPATH += .
INCLUDEPATH += ../CAN_Analyser_USB_Driver/.
INCLUDEPATH += ../CAN_Analyser_USB_Driver/hidapi/.

LIBS += -lusb_driver -L../../CAN_Analyser_USB_Driver/
LIBS += -lhidapi -L../../CAN_Analyser_USB_Driver/hidapi/

SOURCES += main.cpp\
        mainwindow.cpp \
    mysquare.cpp \
    msgmodel.cpp \
    msgdelegate.cpp \
    msg.cpp \
    idmodel.cpp \
    msgtypemodel.cpp \
    idrep.cpp \
    msgtyperep.cpp \
    msgiddelegate.cpp \
    csvmsgpackethandler.cpp \
    devicehandler.cpp \
    userrolemngr.cpp \
    msgproxymodel.cpp \
    msgfilterproxymodel.cpp \
    msglimitfilterproxy.cpp \
    msgtableview.cpp \
    idcompleter.cpp \
    hugeqvector.cpp

HEADERS  += mainwindow.h \
    mysquare.h \
    msgmodel.h \
    msgdelegate.h \
    msg.h \
    idmodel.h \
    msgtypemodel.h \
    idrep.h \
    msgtyperep.h \
    msgiddelegate.h \
    csvmsgpackethandler.h \
    devicehandler.h \
    userrolemngr.h \
    msgproxymodel.h \
    r_ringbuffer.h \
    msgfilterproxymodel.h \
    msglimitfilterproxy.h \
    msgtableview.h \
    idcompleter.h \
    hugeqvector.h

FORMS    += mainwindow.ui \

RESOURCES += \
    ressources.qrc


include(SystemOverview/SystemOverview.pri)
include(SendMessages/SendMessages.pri)
include(MessageConfig/MessageConfig.pri)
