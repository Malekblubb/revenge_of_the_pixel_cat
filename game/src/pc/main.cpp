//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/core/engine.hpp>
#include <pc/core/game.hpp>
#include <pc/core/game_window.hpp>
#include <pc/shared/datamanager.hpp>
#include <pc/core/engine.inl>

int main() {
	// create all components (TODO: maybe do this automated)
	pc::GameWindow*	 gameWindow  = new pc::GameWindow{{1280, 720}, "The Revenge of the Pixelcat"};
	pc::Game*        game        = new pc::Game;
	pc::GameUpdater* gameUpdater = new pc::GameUpdater;
	pc::Input*       input       = new pc::Input;
	pc::Render*      render      = new pc::Render{gameWindow->renderWindow()};
	pc::DataManager* dataManager = new pc::DataManager{"data"};

	pc::EngineT engine {
			gameWindow,
			game,
			gameUpdater,
			input,
			render,
			dataManager
	};
	engine.initializeAll();
	
	// run the game
	auto ret(gameWindow->run());
	
	// clean up memory
	delete gameWindow;
	delete game;
	delete gameUpdater;
	delete input;
	delete render;
	delete dataManager;
	
	return ret;
}
