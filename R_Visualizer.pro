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
    ideditordelegate.cpp \
    msgtypeeditordelegate.cpp \
    idadddialog.cpp \
    msgtypeadddialog.cpp \
    csvmsgpackethandler.cpp \
    msgtypeformatterdialog.cpp \
    devicehandler.cpp

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
    ideditordelegate.h \
    msgtypeeditordelegate.h \
    idadddialog.h \
    msgtypeadddialog.h \
    csvmsgpackethandler.h \
    msgtypeformatterdialog.h \
    devicehandler.h

FORMS    += mainwindow.ui \
    idadddialog.ui \
    msgtypeadddialog.ui \
    msgtypeformatterdialog.ui

RESOURCES += \
    ressources.qrc
