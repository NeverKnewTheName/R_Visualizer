# vim:ft=make
#-------------------------------------------------
#
# Project created by QtCreator 2015-02-03T16:04:14
#
#-------------------------------------------------

QT       -= gui

TARGET = usb_driver

TEMPLATE = lib

CONFIG += silent release dll plugin

DEFINES += USB_DRIVER_LIBRARY

INCLUDEPATH += ./hidapi/.

LIBS += -L../../CAN_Analyser_USB_Driver/hidapi -lhidapi

SOURCES += devicedriver.cpp \
    can_packet.cpp \
    data_packet.cpp \
    error_packet.cpp

HEADERS += devicedriver.h \
    usb_driver_global.h \
    can_packet.h \
    data_packet.h \
    error_packet.h


unix {
    DESTDIR=../lib

    OBJECTS_DIR = .build
    MOC_DIR     = .build
    UI_DIR      = .build
    RCC_DIR     = .build
}

win32 {
    DESTDIR = $$PWD
}
