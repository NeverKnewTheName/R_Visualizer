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
    r_vis_mcu.cpp \
    r_vis_timer.cpp \
    r_vis_lifetimer.cpp \
    r_vis_intcontroller.cpp \
    mysquare.cpp

HEADERS  += mainwindow.h \
    r_vis_mcu.h \
    r_vis_timer.h \
    r_vis_lifetimer.h \
    r_vis_intcontroller.h \
    mysquare.h

FORMS    += mainwindow.ui

RESOURCES += \
    ressources.qrc
