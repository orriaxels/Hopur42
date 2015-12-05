QT += core sql
QT -= gui

TARGET = VLN1-Skil
CONFIG += console
CONFIG -= app_bundle
CONFIG += C++11

TEMPLATE = app

SOURCES += main.cpp \
    models/persons.cpp \
    services/service.cpp \
    ui/interface.cpp \
    repo/repository.cpp \
    models/computers.cpp \
    util/objectsort.cpp

HEADERS +=  \
    models/persons.h \
    services/service.h \
    ui/interface.h \
    repo/repository.h \
    models/computers.h \
    initdatabaseconnect.h \
    util/objectsort.h
