//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_MAIN_WINDOW_HPP
#define PCE_MAIN_WINDOW_HPP


#include "graphics_manager.hpp"

#include <QMainWindow>


namespace Ui
{class main_window;}


namespace pce
{
	class main_window : public QMainWindow
	{
		Q_OBJECT

		// ui
		Ui::main_window* m_ui;
		
		graphics_manager m_graphicsmgr;

	public:
		explicit main_window(QWidget* parent = nullptr);
		virtual ~main_window();

	private slots:
		void on_pb_reset_scale_clicked();
		
	private:
		void init();
	};
}

#endif // PCE_MAIN_WINDOW_HPP
