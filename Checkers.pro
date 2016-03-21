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
    darksquare.cpp \
    piece.cpp \
    checkerboardgui.cpp

HEADERS  += mainwindow.hpp \
    darksquare.hpp \
    piece.hpp \
    squaresizes.hpp \
    checkerboardgui.hpp

FORMS    += mainwindow.ui
