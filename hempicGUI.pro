#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T15:33:24
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hempicGUI
TEMPLATE = app


SOURCES += main.cpp\
        hempicgui.cpp \
    cambiarfecha.cpp

HEADERS  += hempicgui.h \
    cambiarfecha.h

FORMS    += hempicgui.ui \
    cambiarfecha.ui

RESOURCES += \
    resources.qrc
