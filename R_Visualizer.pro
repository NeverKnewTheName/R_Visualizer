#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T14:29:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = R_Visualizer
TEMPLATE = app


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
    csvhandler.cpp

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
    csvhandler.h

FORMS    += mainwindow.ui \
    idadddialog.ui \
    msgtypeadddialog.ui

RESOURCES += \
    ressources.qrc
