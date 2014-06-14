//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/constants.hpp>
#include <pce/start_checker.hpp>
#include <iostream>

namespace pce
{
	start_checker::start_checker() :
		m_valid{true}
	{ }
	
	void start_checker::work()
	{
		for(auto& a : m_work)
		{
			std::string error_str;
			bool success{true};
			a(success, error_str);
			if(!success)
				m_errorstream << error_str << "\n\n";
		}
		
		m_valid = m_errorstream.str().size() <= 0;
	}	
}
