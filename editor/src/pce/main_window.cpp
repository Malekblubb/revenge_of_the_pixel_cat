//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/main_window.hpp>
#include "ui_main_window.h"


namespace pce
{
	main_window::main_window(QWidget* parent) :
		QMainWindow{parent},
		m_ui{new Ui::main_window},
		m_graphicsmgr{"graphics"}
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
		// connect
		// send key input from list widget to edit area
		this->connect(m_ui->lw_tilesets, SIGNAL(key_pressed(QKeyEvent*)), m_ui->w_edit_area, SLOT(key_pressed(QKeyEvent*)));
		this->connect(m_ui->lw_tilesets, SIGNAL(key_released(QKeyEvent*)), m_ui->w_edit_area, SLOT(key_released(QKeyEvent*)));
		
		// add image names to list
		for(const auto& a : m_graphicsmgr.images())
			m_ui->lw_tilesets->addItem(a.first.c_str());
	}
}
