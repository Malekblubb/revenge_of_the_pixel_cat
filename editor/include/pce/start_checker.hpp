//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_START_CHECKER_HPP
#define PCE_START_CHECKER_HPP


#include <mlk/signals_slots/slot.h>

#include <sstream>
#include <vector>


namespace pce
{	
	class start_checker
	{		
		bool m_valid;
		std::ostringstream m_errorstream;
		std::vector<mlk::slot<bool&, std::string&>> m_work;
		
	public:
		start_checker();
		
		template<typename Work_Func>
		void add_work(Work_Func&& wf)
		{m_work.emplace_back(wf);}
		
		auto valid() const noexcept
		{return m_valid;}
		
		auto error_string() const
		{return m_errorstream.str();}
		
		void work();
	};
}


#endif // PCE_START_CHECKER_HPP
