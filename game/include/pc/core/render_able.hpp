//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_RENDERABLE_HPP
#define PC_CORE_RENDERABLE_HPP

#include <SFML/Graphics.hpp>

namespace pc {
	
	struct RenderAble {
		virtual void render(sf::RenderTarget& target) = 0;
	};
	
}

#endif // PC_CORE_RENDERABLE_HPP
