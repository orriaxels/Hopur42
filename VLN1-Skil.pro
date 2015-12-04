QT += core sql
QT -= gui

TARGET = VLN1-Skil
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    models/persons.cpp \
    services/service.cpp \
    ui/interface.cpp \
    repo/repository.cpp

HEADERS +=  \
    models/persons.h \
    services/service.h \
    ui/interface.h \
    repo/repository.h
