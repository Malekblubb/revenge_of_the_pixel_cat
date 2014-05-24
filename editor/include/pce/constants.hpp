//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_CONSTANTS_HPP
#define PCE_CONSTANTS_HPP


#include <string>


namespace pce
{
	namespace constants
	{
		inline const auto& graphics_path()
		{
			static std::string s{"graphics"};
			return s;
		}
	}
}


#endif // PCE_CONSTANTS_HPP 
