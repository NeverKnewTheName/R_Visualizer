# vim:ft=make
#-------------------------------------------------
#
# Project created by QtCreator 2015-02-03T16:04:14
#
#-------------------------------------------------

QT       -= gui

TARGET = hidapi
TEMPLATE = lib

CONFIG += silent release dll plugin

DEFINES += HIDAPI_LIBRARY

HEADERS += hidapi.h\
           hidapi_global.h

unix {
    SOURCES += linux/hid-libusb.c
    LIBS += -lusb-1.0 -ludev

    DESTDIR=../lib

    OBJECTS_DIR = .build
    MOC_DIR     = .build
    UI_DIR      = .build
    RCC_DIR     = .build
}

win32 {
    SOURCES += windows/hid.c
    LIBS += -lsetupapi

    DESTDIR = $$PWD
}
