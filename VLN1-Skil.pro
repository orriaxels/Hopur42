QT += core
QT -= gui

TARGET = VLN1-Skil
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    interface.h \
    persons.h \
    repository.h \
    service.h

SOURCES += \
    interface.cpp \
    main.cpp \
    persons.cpp \
    repository.cpp \
    service.cpp
