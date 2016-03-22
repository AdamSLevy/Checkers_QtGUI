#-------------------------------------------------
#
# Project created by QtCreator 2016-01-28T22:32:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Checkers
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    darksquare.cpp \
    checkerboardgui.cpp \
    checkers/checkerboard.cpp \
#    checkers/ffnn.cpp \
#    checkers/minimax.cpp \
    pieceg.cpp \

HEADERS  += mainwindow.hpp \
    darksquare.hpp \
    squaresizes.hpp \
    checkerboardgui.hpp \
    checkers/bit_mask_init.h \
    checkers/checkerboard.hpp \
#    checkers/ffnn.hpp \
#    checkers/minimax.hpp \
#    checkers/ThrowAssert.hpp \
    pieceg.hpp

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -Wno-inconsistent-missing-override

#LIBS += -L/usr/local/lib -larmadillo
#INCLUDEPATH += /usr/local/Cellar/armadillo/6.500.4/include
#DEPENDPATH += /usr/local/Cellar/armadillo/6.500.4/include
