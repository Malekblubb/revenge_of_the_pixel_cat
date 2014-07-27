//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/constants.hpp>
#include <pce/main_window.hpp>
#include "ui_main_window.h"

#include <QFileDialog>
#include <QMessageBox>


namespace pce
{
	main_window::main_window(QWidget* parent) :
		QMainWindow{parent},
		m_ui{new Ui::main_window},
		m_graphicsmgr{constants::graphics_path()}
	{
		m_ui->setupUi(this);
		this->init();
	}
	
	main_window::~main_window()
	{
		delete m_ui;
	}
	
	// -------- load / save --------
	void main_window::on_pb_save_clicked()
	{
		m_lvmgr.save(QFileDialog{}.getSaveFileName().toStdString());
	}
	
	
	// -------- graphics list --------
	void main_window::on_lw_tilesets_itemSelectionChanged()
	{
	    m_edit_area->repaint_request();
	}
	
	
	// -------- layer settings --------
	void main_window::on_lw_layers_currentRowChanged(int row)
	{
		if(row == -1)
		{
			m_ui->gb_layer_settings->setEnabled(false);
			return;
		}
		
		// set ui
		m_ui->gb_layer_settings->setEnabled(true);
		
		this->update_layer_settings();
		m_edit_area->repaint_request();
	}
	
	void main_window::on_sb_layer_width_editingFinished()
	{
		auto* layer(m_layermgr.selected_layer());
		
		if(layer == nullptr)
			return;
		
		layer->set_size(m_ui->sb_layer_width->value(), layer->num_tiles_y());
		m_edit_area->repaint_request();
	}
	
	void main_window::on_sb_layer_height_editingFinished()
	{
		auto* layer(m_layermgr.selected_layer());
		
		if(layer == nullptr)
			return;
		
		layer->set_size(layer->num_tiles_x(), m_ui->sb_layer_height->value());
		m_edit_area->repaint_request();
	}
	
	void main_window::on_sb_layer_pos_x_valueChanged(int value)
	{
		auto* layer(m_layermgr.selected_layer());
		
		if(layer == nullptr)
			return;
		
		layer->set_position_x(value);
		m_edit_area->repaint_request();
	}
	
	void main_window::on_sb_layer_pos_y_valueChanged(int value)
	{
		auto* layer(m_layermgr.selected_layer());
		
		if(layer == nullptr)
			return;
		
		layer->set_position_y(value);
		m_edit_area->repaint_request();
	}
	
	void main_window::on_pb_use_layer_image_clicked()
	{
		if(m_ui->lw_tilesets->currentRow() == -1)
		{
			QMessageBox::warning(this, "Failed to set image", "There is no graphic selected currently.");
			return;
		}
		
		auto name(m_ui->lw_tilesets->currentItem()->text().toStdString());	
		auto* layer(m_layermgr.selected_layer());
		if(layer != nullptr)
			layer->set_image(&m_graphicsmgr.images().at(name), name);
		
		m_ui->le_layer_image->setText(name.c_str());
		m_ui->lw_layers->currentItem()->setText(layer->name().c_str());
		m_edit_area->repaint_request();
	}
	
	
	// -------- global edit_area functions --------
	void main_window::on_pb_reset_scale_clicked()
	{
		m_edit_area->scale_change_requested(100);
	}
	
	// global translate
	void main_window::on_pb_translate_left_clicked()
	{
		m_edit_area->translate_x_request(-m_ui->sb_translate_step_x->value());
		m_edit_area->repaint_request();
	}
	
	void main_window::on_pb_translate_right_clicked()
	{
		m_edit_area->translate_x_request(m_ui->sb_translate_step_x->value());
		m_edit_area->repaint_request();
	}
	
	void main_window::on_pb_translate_down_clicked()
	{
		m_edit_area->translate_y_request(m_ui->sb_translate_step_y->value());
		m_edit_area->repaint_request();
	}
	
	void main_window::on_pb_translate_up_clicked()
	{
		m_edit_area->translate_y_request(-m_ui->sb_translate_step_y->value());
		m_edit_area->repaint_request();
	}
	
	void main_window::on_sb_view_x_valueChanged(int value)
	{
		m_edit_area->set_translate_x(static_cast<qreal>(value));
		m_edit_area->repaint_request();
	}
	
	void main_window::on_sb_view_y_valueChanged(int value)
	{
		m_edit_area->set_translate_y(static_cast<qreal>(value));
		m_edit_area->repaint_request();
	}
	
	// brush settings
	void main_window::on_pb_r_180_clicked()
	{
	    m_edit_area->brush_rotate_180_request();
		m_edit_area->repaint_request();
	}
	
	void main_window::on_pb_r_90_clicked()
	{
	    m_edit_area->brush_rotate_90_request();
		m_edit_area->repaint_request();
	}
	
	void main_window::on_pb_flip_hor_clicked()
	{
	    m_edit_area->brush_flip_horizontal_request();
		m_edit_area->repaint_request();
	}
	
	void main_window::on_pb_flip_vert_clicked()
	{
		m_edit_area->brush_flip_vertical_request();
		m_edit_area->repaint_request();
	}
	
	// -------- slots called from other objects --------
	void main_window::update_layer_settings()
	{
		if(m_ui->lw_layers->currentRow() == -1)
			return;
		
		auto* layer(m_layermgr.from_rowindex(m_ui->lw_layers->currentRow()));
		m_ui->sb_layer_width->setValue(layer->num_tiles_x());
		m_ui->sb_layer_height->setValue(layer->num_tiles_y());
		
		m_ui->sb_layer_pos_x->setValue(layer->position().x());
		m_ui->sb_layer_pos_y->setValue(layer->position().y());
		
		m_ui->le_layer_image->setText(layer->image_name().c_str());
	}
	
	void main_window::edit_area_global_translate_changed()
	{
		auto& newt(m_edit_area->global_translate());
		m_ui->sb_view_x->setValue(newt.x());
		m_ui->sb_view_y->setValue(newt.y());
	}
	
	
	void main_window::timer_update()
	{
		if(m_statusmgr.need_update())
			m_statusmgr.update();
	}
	
	
	void main_window::init()
	{
		m_update_timer.setInterval(0);
		
		// init all pointers
		m_edit_area = m_ui->w_edit_area;
		
		m_edit_area->set_graphicsmgr(&m_graphicsmgr);
		m_edit_area->set_layermgr(&m_layermgr);
		m_edit_area->set_statusmgr(&m_statusmgr);
		m_edit_area->set_ui(m_ui);
		
		m_layermgr.set_ui(m_ui);
		
		m_lvmgr.set_editarea(m_edit_area);
		m_lvmgr.set_ui(m_ui);
		
		m_statusmgr.set_ui(m_ui);
		
		
		// connect		
		// -------- this --------
		this->connect(&m_update_timer, SIGNAL(timeout()), this, SLOT(timer_update()));
		this->connect(&m_statusmgr, SIGNAL(start_update()), &m_update_timer, SLOT(start()));
		this->connect(&m_statusmgr, SIGNAL(stop_update()), &m_update_timer, SLOT(stop()));
		
		// -------- EDIT AREA --------
		// send key input from list widget to edit area
		this->connect(m_ui->lw_tilesets, SIGNAL(key_pressed(QKeyEvent*)), m_edit_area, SLOT(key_pressed(QKeyEvent*)));
		this->connect(m_ui->lw_tilesets, SIGNAL(key_released(QKeyEvent*)), m_edit_area, SLOT(key_released(QKeyEvent*)));

		this->connect(m_edit_area, SIGNAL(layer_moved()), this, SLOT(update_layer_settings()));
		this->connect(m_edit_area, SIGNAL(global_translate_changed()), this, SLOT(edit_area_global_translate_changed()));
		
		// grid
		this->connect(m_ui->cb_showgrid, SIGNAL(toggled(bool)), m_edit_area, SLOT(grid_state_changed(bool)));
		this->connect(m_ui->sb_grid_x, SIGNAL(valueChanged(QString)), m_edit_area, SLOT(grid_update_requested(QString)));
		this->connect(m_ui->sb_grid_y, SIGNAL(valueChanged(QString)), m_edit_area, SLOT(grid_update_requested(QString)));
		this->connect(m_ui->le_gridcolor, SIGNAL(textChanged(QString)), m_edit_area, SLOT(grid_update_requested(QString)));
		
		// scale
		this->connect(m_ui->sb_scale, SIGNAL(valueChanged(int)), m_edit_area, SLOT(scale_change_requested(int)));
		
		
		// -------- LAYER LIST --------
		this->connect(m_ui->pb_add_layer, SIGNAL(clicked()), &m_layermgr, SLOT(add_layer_request()));
		this->connect(m_ui->pb_remove_layer, SIGNAL(clicked()), &m_layermgr, SLOT(remove_layer_request()));
		
		
		// add image names to list
		for(const auto& a : m_graphicsmgr.images())
			m_ui->lw_tilesets->addItem(a.first.c_str());
	}
}
