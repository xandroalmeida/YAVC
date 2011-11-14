#-------------------------------------------------
#
# Project created by QtCreator 2010-12-28T21:04:24
#
#-------------------------------------------------

QT       += core gui

TARGET = YAVC
TEMPLATE = app
RC_FILE = yavc.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    optionsdialog.cpp \
    aboutdialog.cpp \
    movieinfo.cpp \
    videoprofile.cpp \
    settings.cpp \
    movieconvertthread.cpp

HEADERS  += mainwindow.h \
    optionsdialog.h \
    aboutdialog.h \
    movieinfo.h \
    videoprofile.h \
    settings.h \
    movieconvertthread.h

FORMS    += mainwindow.ui \
    optionsdialog.ui \
    aboutdialog.ui

OTHER_FILES += \
    info/profiles.xml \
    README

RESOURCES += \
    icons.qrc






