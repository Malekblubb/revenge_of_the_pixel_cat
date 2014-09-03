//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_COMMON_HPP
#define PC_COMMON_HPP

#include <pc/core/engine.hpp>

#include <mlk/log/log.h>
#include <mlk/types/types.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>

namespace pc {
	// forwards
	class Game;
	class GameWindow;
	class GameUpdater;
	class Input;	
	
	// typedefs
	using EngineT = Engine<
							GameWindow,
							Game,
							GameUpdater,
							Input>;
	using Fd = float;
	using Key = sf::Keyboard::Key;
	using Button = sf::Mouse::Button;
	using Vec2f = sf::Vector2f;
	using Vec2i = sf::Vector2i;
	using Vec2u = sf::Vector2u;
	using Vec3f = sf::Vector3f;
	using Vec3i = sf::Vector3i;
	
	// enums
	enum class MouseWheel : int {
		Down,
		Up
	};
}

#endif // PC_COMMON_HPP 
