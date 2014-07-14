//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_LEVEL_MANAGER_HPP
#define PCE_LEVEL_MANAGER_HPP


namespace pce
{
	class level_manager
	{
		class edit_area* m_editarea;
		
	public:
		level_manager();
		
		void set_editarea(class edit_area* ea) noexcept
		{m_editarea = ea;}
		
		bool load();
		bool save();
	};
}


#endif // PCE_LEVEL_MANAGER_HPP
