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
INCLUDEPATH += ../CAN_Analyser_USB_Driver/hidapi/.
INCLUDEPATH += ../CAN_Analyser_USB_Driver/.

LIBS += -L../../CAN_Analyser_USB_Driver/hidapi/ -lhidapi
LIBS += -L../../CAN_Analyser_USB_Driver/ -lusb_driver

SOURCES += main.cpp\
        mainwindow.cpp \
    csvmsgpackethandler.cpp \
    devicehandler.cpp \
    userrolemngr.cpp \
    msgparser.cpp

HEADERS  += mainwindow.h \
    csvmsgpackethandler.h \
    devicehandler.h \
    userrolemngr.h \
    msgparser.h

FORMS    += mainwindow.ui

RESOURCES += \
    ressources.qrc


include(Msg/Msg.pri)
include(../R_Visualizer_Utilities/R_Visualizer_Utilities.pri)
include(SystemOverview/SystemOverview.pri)
include(SendMessages/SendMessages.pri)
include(MessageConfig/MessageConfig.pri)
include(ErrLogView/ErrLogView.pri)
