//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/main_window.hpp>

#include <QApplication>


int main(int argc, char *argv[])
{
	QApplication app{argc, argv};
	pce::main_window window;
	window.show();

	return app.exec();
}
