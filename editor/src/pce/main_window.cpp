//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/main_window.hpp>
#include "ui_main_window.h"


namespace pce
{
	main_window::main_window(QWidget* parent) :
		QMainWindow{parent}
	{
		m_ui->setupUi(this);
	}
}
