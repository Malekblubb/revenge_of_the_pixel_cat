//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_MAIN_WINDOW_HPP
#define PCE_MAIN_WINDOW_HPP


#include "graphics_manager.hpp"
#include "layer_manager.hpp"

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
		
		class edit_area* m_edit_area;
		graphics_manager m_graphicsmgr;
		layer_manager m_layermgr;

	public:
		explicit main_window(QWidget* parent = nullptr);
		virtual ~main_window();

	private slots:
		void on_pb_reset_scale_clicked();
		void on_lw_layers_currentRowChanged(int row);
		void on_sb_layer_width_valueChanged(int value);
		void on_sb_layer_height_valueChanged(int value);
		void on_sb_layer_pos_x_valueChanged(int value);
		void on_sb_layer_pos_y_valueChanged(int value);
		void on_pb_translate_left_clicked();
		void on_pb_translate_right_clicked();
		void on_pb_translate_down_clicked();
		void on_pb_translate_up_clicked();
		void on_sb_view_x_valueChanged(int value);
		void on_sb_view_y_valueChanged(int value);
		
		void update_layer_settings();
		void edit_area_global_translate_changed();
		
	private:
		void init();
	};
}

#endif // PCE_MAIN_WINDOW_HPP
