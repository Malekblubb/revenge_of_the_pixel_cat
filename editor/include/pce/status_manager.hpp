//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_STATUS_MANAGER_HPP
#define PCE_STATUS_MANAGER_HPP


#include <mlk/time/simple_timer.h>

#include <QObject>

#include <deque>
#include <string>


namespace Ui
{class main_window;}

namespace pce
{
	class status_manager : public QObject
	{
		Q_OBJECT
		
		mlk::tm::simple_timer m_timer;
		std::deque<std::string> m_queue;
		class QLabel* m_label;
		
		Ui::main_window* m_ui;
				
	public:
		status_manager(QWidget* parent = nullptr);
		
		void update();
		
		void set_ui(Ui::main_window* ui) noexcept;
		
		void new_entry(const std::string& text);
		
		bool need_update() const noexcept
		{return !m_queue.empty();}
		
	signals:
		// don't spam the main_window
		void start_update();
		void stop_update();
	};
}


#endif // PCE_STATUS_MANAGER_HPP
