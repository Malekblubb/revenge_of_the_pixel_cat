//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include "ui_main_window.h"
#include <pce/level_manager.hpp>





namespace pce
{
	level_manager::level_manager()
	{ }
	
	
	bool level_manager::load()
	{
		
	}
	
	bool level_manager::save(const std::string& filename)
	{
		if(!m_lvgen.generate())
			return false;
		
		return true;
	}
}