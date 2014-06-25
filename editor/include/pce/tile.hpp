//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_TILE_HPP
#define PCE_TILE_HPP


namespace pce
{
	enum tile_flag : int
	{
		flip_horizontal = 0x01,
		flip_vertical = 0x02
	};
	
	struct tile
	{
		int index;
		int flags;
		double rotation;
	};
}


#endif // PCE_TILE_HPP
