//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_MAIN_WINDOW_HPP
#define PCE_MAIN_WINDOW_HPP


#include "graphics_manager.hpp"
#include "layer_manager.hpp"
#include "level_manager.hpp"
#include "status_manager.hpp"

#include <QMainWindow>
#include <QTimer>


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
		level_manager m_lvmgr;
		status_manager m_statusmgr;
		
		QTimer m_update_timer;

	public:
		explicit main_window(QWidget* parent = nullptr);
		virtual ~main_window();

	private slots:
		void on_pb_save_clicked();
		void on_lw_tilesets_itemSelectionChanged();
		void on_pb_reset_scale_clicked();
		void on_lw_layers_currentRowChanged(int row);
		void on_sb_layer_width_editingFinished();
		void on_sb_layer_height_editingFinished();
		void on_sb_layer_pos_x_valueChanged(int value);
		void on_sb_layer_pos_y_valueChanged(int value);
		void on_pb_translate_left_clicked();
		void on_pb_translate_right_clicked();
		void on_pb_translate_down_clicked();
		void on_pb_translate_up_clicked();
		void on_sb_view_x_valueChanged(int value);
		void on_sb_view_y_valueChanged(int value);
		void on_pb_r_180_clicked();
		void on_pb_r_90_clicked();
		void on_pb_flip_hor_clicked();
		void on_pb_flip_vert_clicked();
		void on_pb_use_layer_image_clicked();
		
		void update_layer_settings();
		void edit_area_global_translate_changed();
		
		void timer_update();
		
	private:
		void init();
	};
}

#endif // PCE_MAIN_WINDOW_HPP
