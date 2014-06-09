//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include "ui_main_window.h"
#include <pce/constants.hpp>
#include <pce/layer_manager.hpp>
#include <pce/list_widget_layer_item.hpp>


namespace pce
{
	layer_manager::layer_manager(QWidget* parent) :
		QObject{parent},
		m_current_id{0}
	{ }
	
	
	void layer_manager::set_ui(Ui::main_window* ui) noexcept
	{m_ui = ui;}
	
	void layer_manager::add_layer(const layer& l)
	{
		// add to layers
		auto index(this->get_newid());
		m_layers[index] = l;
		
		// add to ui
		auto* w(new list_widget_layer_item{index});
		m_ui->lw_layers->addItem(w);
	}
	
	void layer_manager::remove_layer(int index)
	{
		delete m_ui->lw_layers->item(index);
	}
	
	
	void layer_manager::add_layer_request()
	{this->add_layer({constants::default_layersize(), constants::default_layersize()});}
	
	void layer_manager::remove_layer_request()
	{this->remove_layer(m_ui->lw_layers->currentRow());}
	
	
	int layer_manager::get_newid() noexcept
	{return m_current_id++;}
}
