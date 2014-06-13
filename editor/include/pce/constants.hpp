//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_CONSTANTS_HPP
#define PCE_CONSTANTS_HPP


#include <string>

#include <QPoint>


namespace pce
{
	namespace constants
	{
		inline const auto& graphics_path()
		{
			static std::string s{"graphics"};
			return s;
		}
		
		inline int default_layersize()
		{return 16;}
		
		inline QPoint coords_from_tileindex(int index, int tile_size = 64)
		{return {(index % 16) * tile_size, (index /16) * tile_size};}
	}
}


#endif // PCE_CONSTANTS_HPP 
