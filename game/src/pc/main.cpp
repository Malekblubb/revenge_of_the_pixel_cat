//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/core/engine.hpp>
#include <pc/core/game.hpp>
#include <pc/core/game_updater.hpp>
#include <pc/core/game_window.hpp>
#include <pc/core/input.hpp>

int main() {
	// create all components
	pc::GameWindow*		gameWindow	= new pc::GameWindow{{400, 400}, "The Revenge of the Pixelcat"};
	pc::Game*			game		= new pc::Game;
	pc::GameUpdater*	gameUpdater = new pc::GameUpdater;
	pc::Input*			input		= new pc::Input;
	
	pc::EngineT engine{
		gameWindow,
		game,
		gameUpdater,
		input
	};
	engine.initializeAll();
	
	return engine.getComponent<pc::GameWindow>()->run();
}
