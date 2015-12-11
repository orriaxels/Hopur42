#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T19:00:39
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tableview2
TEMPLATE = app


SOURCES += main.cpp\
    models/computer.cpp \
    models/scientist.cpp \
    repo/repository.cpp \
    services/service.cpp \
    ui/adddialog.cpp \
    ui/mainwindow.cpp

FORMS    += ui/mainwindow.ui \
    ui/adddialog.ui

HEADERS  += ui/adddialog.h \
    models/computer.h \
    models/scientist.h \
    repo/initdatabase.h \
    repo/repository.h \
    ui/mainwindow.h \
    services/service.h




