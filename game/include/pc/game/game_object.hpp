//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_GAME_GAME_OBJECT_HPP
#define PC_GAME_GAME_OBJECT_HPP

#include <pc/common.hpp>

namespace pc {
	
	class GameObject {
	public:
		virtual void update(Fd) = 0;
		virtual void render() = 0;
	};
	
}

#endif // PC_GAME_GAME_OBJECT_HPP 
