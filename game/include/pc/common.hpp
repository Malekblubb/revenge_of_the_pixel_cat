//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_COMMON_HPP
#define PC_COMMON_HPP

#include <mlk/log/log.h>
#include <mlk/types/types.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>

namespace pc {
	// forwards
	template<typename, typename> class Game;
	class GameUpdater;
	class GameWindow;
	
	// typedefs
	using TGame = Game<GameWindow, GameUpdater>;
	using Fd = float;
}

#endif // PC_COMMON_HPP 
