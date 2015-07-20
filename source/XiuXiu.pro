#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T16:56:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XiuXiu
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp\
           algorithm/facelift.cpp \
    dialog.cpp \
    xqdraw.cpp \
    xqgraphicsview.cpp \
    exif.cpp \
    edgedialog.cpp \
    whitendialog.cpp



HEADERS  += mainwindow.h\
           ./algorithm/*\
            ./model/model.h \
    common/common.h \
    viewmodel/ViewModel.h \
    app/App.h \
    viewmodel/command/opencommand.h \
    common/CommandParameter.h \
    viewmodel/command/faceliftcommand.h \
    algorithm/cmatrix.h \
    algorithm/facelift.h \
    viewmodel/conver.h \
    algorithm/baseoperation.h \
    viewmodel/command/graycommand.h \
    algorithm/facewhite.h \
    viewmodel/command/undocommand.h \
    viewmodel/command/histcommand.h \
    viewmodel/command/crystalcommand.h \
    viewmodel/command/facewhitecommand.h \
    viewmodel/command/reancientcommand.h \
    viewmodel/command/pencilcommand.h \
    algorithm/trangaussianblur.h \
    viewmodel/command/gausscommand.h \
    algorithm/mathfunction.h \
    viewmodel/command/horizontalcommand.h \
    algorithm/edge.h \
    viewmodel/command/verticalcommand.h \
    dialog.h \
    xqdraw.h \
    xqgraphicsview.h \
    viewmodel/command/clockrotcommand.h \
    viewmodel/command/anticlorotcommand.h \
    exif.h \
    viewmodel/command/luminandcontras.h \
    viewmodel/command/gammacommand.h \
    viewmodel/command/hueandsaturation.h \
    viewmodel/command/doadjustcommand.h \
    viewmodel/command/docancelcommand.h \
    viewmodel/command/redocommand.h \
    edgedialog.h \
    viewmodel/command/edgecommand.h \
    whitendialog.h \
    viewmodel/command/acgcommand.h

FORMS    += mainwindow.ui \
    dialog.ui \
    edgedialog.ui \
    whitendialog.ui

INCLUDEPATH += /usr/local/Cellar/opencv/3.0.0/include \
                /usr/local/Cellar/opencv/3.0.0/include/opencv \
                /usr/local/Cellar/opencv/3.0.0/include/opencv2

LIBS +=   /usr/local/Cellar/opencv/3.0.0/lib/*.dylib

RESOURCES += \
    resources.qrc
