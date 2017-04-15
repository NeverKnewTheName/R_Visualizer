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
INCLUDEPATH += ./inc
INCLUDEPATH += ../CAN_Analyser_USB_Driver/hidapi/
INCLUDEPATH += ../CAN_Analyser_USB_Driver/


SOURCES += \

HEADERS  += \

FORMS    += \

RESOURCES += \
    ./res/ressources.qrc

unix {
    LIBS += -L../CAN_Analyser_USB_Driver/lib -lusb_driver -lhidapi

    OBJECTS_DIR = .build
    MOC_DIR     = .build
    UI_DIR      = .build
    RCC_DIR     = .build
}

win32 {
    LIBS += -L../CAN_Analyser_USB_Driver/hidapi/ -lhidapi
    LIBS += -L../CAN_Analyser_USB_Driver/ -lusb_driver
}

include(MainWindow/MainWindow.pri)
include(InterfaceHandler/InterfaceHandler.pri)
include(UserRoleManager/UserRoleManager.pri)
include(../R_Visualizer_Utilities/R_Visualizer_Utilities.pri)
include(Utils/Utils.pri)
include(FileParser/FileParser.pri)
include(Msg/Msg.pri)
include(MessageStorage/MessageStorage.pri)
include(MessageStream/MessageStream.pri)
#include(SystemOverview/SystemOverview.pri)
#include(SendMessages/SendMessages.pri)
include(MessageConfig/MessageConfig.pri)
include(MessageFilter/MessageFilter.pri)
include(ErrLogView/ErrLogView.pri)
