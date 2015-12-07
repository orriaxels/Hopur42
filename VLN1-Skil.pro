QT += core sql
QT -= gui

TARGET = VLN1-Skil
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ui/interface.cpp \
    models/persons.cpp \
    models/computers.cpp \
    services/service.cpp \
    repo/repository.cpp \
    util/inputcheck.cpp

HEADERS +=  \
    ui/interface.h \
    models/persons.h \
    models/computers.h \
    services/service.h \
    repo/repository.h \
    util/inputcheck.h \
    util/initdatabaseconnect.h
