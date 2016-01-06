#-------------------------------------------------
#
# Project created by QtCreator 2015-08-03T22:05:11
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app



SOURCES += main.cpp \
    cartoon.cpp \
    myscence.cpp \
    myitem.cpp \
    optiondialog.cpp \
    aboutdialog.cpp \
    finishdialog.cpp \
    statisticsdialog.cpp

HEADERS  += \
    cartoon.h \
    myscence.h \
    myitem.h \
    optiondialog.h \
    aboutdialog.h \
    finishdialog.h \
    statisticsdialog.h

RESOURCES += \
    images.qrc

FORMS += \
    optiondialog.ui \
    aboutdialog.ui \
    finishdialog.ui \
    statisticsdialog.ui

OTHER_FILES += \
    my.rc
    RC_FILE = my.rc
