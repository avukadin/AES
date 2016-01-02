QT += core
QT -= gui

CONFIG += c++11

TARGET = untitled1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    source_matrix.cpp \
    key_matrix.cpp
CONFIG +=c++11
HEADERS += \
    source_matrix.h \
    key_matrix.h
