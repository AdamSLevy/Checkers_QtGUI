#-------------------------------------------------
#
# Project created by QtCreator 2016-01-28T22:32:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Checkers
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    checkerboard.cpp \
    darksquare.cpp \
    piece.cpp \
    lightsquare.cpp

HEADERS  += mainwindow.h \
    checkerboard.h \
    darksquare.h \
    piece.hpp \
    lightsquare.hpp \
    squaresizes.hpp

FORMS    += mainwindow.ui
