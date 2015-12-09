QT += core sql
QT -= gui

TARGET = VLN1-Skil
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ui/interface.cpp \
    models/scientist.cpp \
    models/computer.cpp \
    services/service.cpp \
    repo/repository.cpp \
    utilities/inputcheck.cpp

HEADERS +=  \
    ui/interface.h \
    models/scientist.h \
    models/computer.h \
    services/service.h \
    repo/repository.h \
    repo/initdatabase.h \
    utilities/inputcheck.h
