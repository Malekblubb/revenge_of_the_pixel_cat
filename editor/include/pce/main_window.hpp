//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_MAIN_WINDOW_HPP
#define PCE_MAIN_WINDOW_HPP


#include <QMainWindow>


namespace Ui
{class main_window;}

namespace pce
{
	class main_window : public QMainWindow
	{
		Q_OBJECT

		Ui::main_window* m_ui;

	public:
		explicit main_window(QWidget* parent = nullptr);

	};
}

#endif // PCE_MAIN_WINDOW_HPP
