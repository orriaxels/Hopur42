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
    ui/adddialog.cpp \
    ui/mainwindow.cpp \
    services/service.cpp \
    repositories/scientistrepository.cpp \
    repositories/computerrepository.cpp \
    models/computer.cpp \
    models/scientist.cpp

FORMS    += ui/mainwindow.ui \
    ui/adddialog.ui

HEADERS  += ui/adddialog.h \
    repo/initdatabase.h \
    ui/mainwindow.h \
    repositories/initdatabase.h \
    services/service.h \
    repositories/computerrepository.h \
    repositories/scientistrepository.h \
    models/computer.h \
    models/scientist.h





