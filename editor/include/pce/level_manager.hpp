//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_LEVEL_MANAGER_HPP
#define PCE_LEVEL_MANAGER_HPP


#include <pce/level_generator.hpp>

#include <string>


namespace Ui
{class main_window;}

namespace pce
{	
	class level_manager
	{
		level_generator m_lvgen;
		
		class edit_area* m_editarea;
		class graphics_manager* m_gmgr;
		Ui::main_window* m_ui;
		
	public:
		level_manager();
		
		void set_editarea(class edit_area* ea) noexcept
		{m_editarea = ea;}
		
		void set_graphicsmgr(class graphics_manager* gmgr) noexcept
		{
			m_gmgr = gmgr;
			m_lvgen.set_gmgr(gmgr);
		}
		
		void set_ui(Ui::main_window* ui) noexcept
		{
			m_ui = ui;
			m_lvgen.set_ui(ui);
		}
		
		bool load();
		bool save(const std::string& filename);
	};
}


#endif // PCE_LEVEL_MANAGER_HPP
