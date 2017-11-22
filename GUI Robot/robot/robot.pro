#-------------------------------------------------
#
# Project created by QtCreator 2012-01-08T18:18:13
#
#-------------------------------------------------

QT       += core gui

CONFIG   += debug

include( examples.pri )


TARGET = robot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    robot.cpp \
    serialhandler.cpp \
    plotwidget.cpp

HEADERS  += mainwindow.h \
    robot.h \
    serialhandler.h \
    plotwidget.h

FORMS    += mainwindow.ui
