//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/constants.hpp>
#include <pce/start_checker.hpp>


namespace pce
{
	start_checker::start_checker() :
		m_graphicsdir{constants::graphics_path()},
		m_valid{true}
	{this->work();}
	
	void start_checker::work()
	{
		if(!m_graphicsdir.exists())
		{
			m_valid = false;
			m_errorstream << "The graphicsdirectory does not exist.\n" <<
							 "Please create it. (Path: " << constants::graphics_path() << ")";
		}
	}	
}
