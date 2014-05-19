#-------------------------------------------------
#
# Project created by QtCreator 2014-05-19T18:47:53
#
#-------------------------------------------------

# qt
QT	    +=	core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# compile settings
QMAKE_CXX = clang++
QMAKE_CXXFLAGS += -std=c++1y -Wno-deprecated-register

# project
TARGET = pixelcat-editor
TEMPLATE = app

INCLUDEPATH +=	include/

SOURCES	    +=	src/pce/main.cpp \
		src/pce/main_window.cpp

HEADERS	    +=	include/pce/main_window.hpp

FORMS	    +=	main_window.ui
