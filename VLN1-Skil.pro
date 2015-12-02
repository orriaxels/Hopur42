QT += core
QT -= gui

TARGET = VLN1-Skil
CONFIG += console
CONFIG -= app_bundle
CONFIG += static

TEMPLATE = app

SOURCES += main.cpp \
    persons.cpp \
    interface.cpp \
    repository.cpp \
    service.cpp

HEADERS += \
    persons.h \
    interface.h \
    repository.h \
    service.h

