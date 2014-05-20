//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/graphics_manager.hpp>


namespace pce
{
	graphics_manager::graphics_manager(const std::string& load_path) :
		m_dir{load_path}
	{this->init();}
	
	void graphics_manager::init()
	{
		for(const auto& a : m_dir.get_content<true>())
		{
			m_images.emplace(a.name, QImage{a.path.c_str()});
		}
	}
}
