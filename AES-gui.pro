#-------------------------------------------------
#
# Project created by QtCreator 2015-12-31T07:17:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AES-gui
TEMPLATE = app

CONFIG += c++11
SOURCES += main.cpp\
        widget.cpp \
    key_matrix.cpp \
    source_matrix.cpp

HEADERS  += widget.h \
    key_matrix.h \
    source_matrix.h

FORMS    += widget.ui
