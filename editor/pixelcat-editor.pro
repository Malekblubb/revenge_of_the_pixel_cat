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

INCLUDEPATH +=	include/ \
		../external/mlk/include/

SOURCES	    +=	src/pce/main.cpp \
		src/pce/main_window.cpp \
		src/pce/edit_area.cpp \
		src/pce/graphics_manager.cpp

HEADERS	    +=	include/pce/main_window.hpp \
		include/pce/edit_area.hpp \
		include/pce/graphics_manager.hpp \
		include/pce/graphicslist_widget.hpp \
		include/pce/constants.hpp

FORMS	    +=	main_window.ui

RESOURCES   +=	assets.qrc
