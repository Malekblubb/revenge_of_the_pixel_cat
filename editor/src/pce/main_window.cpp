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
		m_ui->w_edit_area->set_ui(m_ui);
		
		// connect
		// send key input from list widget to edit area
		this->connect(m_ui->lw_tilesets, SIGNAL(key_pressed(QKeyEvent*)), m_ui->w_edit_area, SLOT(key_pressed(QKeyEvent*)));
		this->connect(m_ui->lw_tilesets, SIGNAL(key_released(QKeyEvent*)), m_ui->w_edit_area, SLOT(key_released(QKeyEvent*)));
		
		// grid
		this->connect(m_ui->cb_showgrid, SIGNAL(toggled(bool)), m_ui->w_edit_area, SLOT(grid_state_changed(bool)));
		this->connect(m_ui->sb_grid_x, SIGNAL(valueChanged(QString)), m_ui->w_edit_area, SLOT(grid_update_requested(QString)));
		this->connect(m_ui->sb_grid_y, SIGNAL(valueChanged(QString)), m_ui->w_edit_area, SLOT(grid_update_requested(QString)));
		this->connect(m_ui->le_gridcolor, SIGNAL(textChanged(QString)), m_ui->w_edit_area, SLOT(grid_update_requested(QString)));
		
		// add image names to list
		for(const auto& a : m_graphicsmgr.images())
			m_ui->lw_tilesets->addItem(a.first.c_str());
	}
}
