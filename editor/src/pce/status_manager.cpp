//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//


#include "ui_main_window.h"
#include <pce/status_manager.hpp>


namespace pce
{
	status_manager::status_manager(QWidget* parent) :
		QObject{parent},
		m_timer{1000}
	{m_timer.run();}
	
	void status_manager::update()
	{
		if(!m_timer.timed_out())
			return;
		
		m_label->setText(m_queue.back().c_str());
		m_queue.pop_back();
		m_timer.restart();
		
		if(!this->need_update())
			emit this->stop_update();
	}
	
	void status_manager::set_ui(Ui::main_window* ui) noexcept
	{
		m_ui = ui;
		m_label = ui->lb_status;
	}
	
	void status_manager::new_entry(const std::string& text)
	{
		m_queue.push_front(text);
		
		if(m_queue.size() == 1)
			emit this->start_update();
	}
}