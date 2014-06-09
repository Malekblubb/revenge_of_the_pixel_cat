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
		src/pce/graphics_manager.cpp \
		src/pce/start_checker.cpp \
		src/pce/brush.cpp \
		src/pce/layer.cpp \
		src/pce/layer_manager.cpp

HEADERS	    +=	include/pce/main_window.hpp \
		include/pce/edit_area.hpp \
		include/pce/graphics_manager.hpp \
		include/pce/graphicslist_widget.hpp \
		include/pce/constants.hpp \
		include/pce/start_checker.hpp \
		include/pce/brush.hpp \
		include/pce/layer.hpp \
		include/pce/tile.hpp \
		include/pce/layer_manager.hpp \
		include/pce/list_widget_layer_item.hpp

FORMS	    +=	main_window.ui

RESOURCES   +=	assets.qrc
