//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/constants.hpp>
#include <pce/main_window.hpp>
#include "ui_main_window.h"


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
	
	void main_window::init()
	{
		// init all pointers
		m_ui->w_edit_area->set_graphicsmgr(&m_graphicsmgr);
		m_ui->w_edit_area->set_layermgr(&m_layermgr);
		m_ui->w_edit_area->set_ui(m_ui);
		
		m_layermgr.set_ui(m_ui);
		
		
		// connect
		// -------- this --------
//		this->connect(m_ui->lw_layers, SIGNAL(currentRowChanged(int)), this, SLOT(on_lw_layers_current_row_changed(int)));
		
		
		// -------- EDIT AREA --------
		// send key input from list widget to edit area
		this->connect(m_ui->lw_tilesets, SIGNAL(key_pressed(QKeyEvent*)), m_ui->w_edit_area, SLOT(key_pressed(QKeyEvent*)));
		this->connect(m_ui->lw_tilesets, SIGNAL(key_released(QKeyEvent*)), m_ui->w_edit_area, SLOT(key_released(QKeyEvent*)));
		
		// grid
		this->connect(m_ui->cb_showgrid, SIGNAL(toggled(bool)), m_ui->w_edit_area, SLOT(grid_state_changed(bool)));
		this->connect(m_ui->sb_grid_x, SIGNAL(valueChanged(QString)), m_ui->w_edit_area, SLOT(grid_update_requested(QString)));
		this->connect(m_ui->sb_grid_y, SIGNAL(valueChanged(QString)), m_ui->w_edit_area, SLOT(grid_update_requested(QString)));
		this->connect(m_ui->le_gridcolor, SIGNAL(textChanged(QString)), m_ui->w_edit_area, SLOT(grid_update_requested(QString)));
		
		// scale
		this->connect(m_ui->sb_scale, SIGNAL(valueChanged(int)), m_ui->w_edit_area, SLOT(scale_change_requested(int)));
		
		
		// -------- LAYER LIST --------
		this->connect(m_ui->pb_add_layer, SIGNAL(clicked()), &m_layermgr, SLOT(add_layer_request()));
		this->connect(m_ui->pb_remove_layer, SIGNAL(clicked()), &m_layermgr, SLOT(remove_layer_request()));
		
		
		// add image names to list
		for(const auto& a : m_graphicsmgr.images())
			m_ui->lw_tilesets->addItem(a.first.c_str());
	}
	
	// custom slots
	void main_window::on_pb_reset_scale_clicked()
	{
		m_ui->w_edit_area->scale_change_requested(100);
	}
	
	void main_window::on_lw_layers_currentRowChanged(int row)
	{
		if(row == -1)
			return;
		
		auto* layer(m_layermgr.from_rowindex(row));
		m_ui->sb_layer_width->setValue(layer->num_tiles_x());
		m_ui->sb_layer_height->setValue(layer->num_tiles_y());
	}
	
	void main_window::on_sb_layer_width_valueChanged(int value)
	{
		auto* layer(m_layermgr.selected_layer());
		
		if(layer == nullptr)
			return;
		
		layer->set_size(value, layer->num_tiles_y());
	}
	
	void main_window::on_sb_layer_height_valueChanged(int value)
	{
		auto* layer(m_layermgr.selected_layer());
		
		if(layer == nullptr)
			return;
		
		layer->set_size(layer->num_tiles_x(), value);
	}
}
