//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_LAYER_MANAGER_HPP
#define PCE_LAYER_MANAGER_HPP


#include "layer.hpp"

#include <map>

#include <QObject>


namespace Ui
{class main_window;}

namespace pce
{
	class layer_manager : public QObject
	{
		Q_OBJECT
		
		std::map<int, layer> m_layers;
		int m_current_id;
		
		Ui::main_window* m_ui;
		
	public:
		layer_manager(QWidget* parent = nullptr);
		
		
		void set_ui(Ui::main_window* ui) noexcept;		
		
		void add_layer(const layer& l);
		void remove_layer(int index);
		
		auto& layers() noexcept
		{return m_layers;}
		
	public slots:
		void add_layer_request();
		void remove_layer_request();
		
	private:
		int get_newid() noexcept;
	};
}


#endif // PCE_LAYER_MANAGER_HPP
