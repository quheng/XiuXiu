#-------------------------------------------------
#
# Project created by QtCreator 2015-07-16T21:30:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = userinterface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    xqdraw.cpp \
    xqgraphicsview.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    xqdraw.h \
    xqgraphicsview.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    resources.qrc
