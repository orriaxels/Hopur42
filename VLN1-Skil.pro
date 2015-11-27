QT += core
QT -= gui

TARGET = VLN1-Skil
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    persons.cpp \
    searchfile.cpp

HEADERS += \
    persons.h \
    searchfile.h

