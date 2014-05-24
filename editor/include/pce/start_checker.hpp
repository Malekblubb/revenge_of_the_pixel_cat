//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_START_CHECKER_HPP
#define PCE_START_CHECKER_HPP


#include <mlk/filesystem/filesystem.h>

#include <sstream>


namespace pce
{
	class start_checker
	{
		mlk::fs::dir_handle m_graphicsdir;
		
		bool m_valid;
		std::ostringstream m_errorstream;
		
	public:
		start_checker();
		
		auto valid() const noexcept
		{return m_valid;}
		
		auto error_string() const
		{return m_errorstream.str();}
		
	private:
		void work();
	};
}


#endif // PCE_START_CHECKER_HPP
