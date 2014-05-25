//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/main_window.hpp>
#include <pce/start_checker.hpp>

#include <mlk/log/log.h>
#include <mlk/tools/utils.h>

#include <QApplication>
#include <QMessageBox>


int main(int argc, char* argv[])
{	
	QApplication app{argc, argv};
	
	// do checks before start app
	pce::start_checker checker;
	if(!checker.valid())
	{
		QMessageBox::critical(nullptr, "Can not start the program", checker.error_string().c_str());
		mlk::exit_with("start checker returned invalid", EXIT_FAILURE, mlk::lerr());
	}
	
	// start window
	pce::main_window window;
	window.show();

	return app.exec();
}
