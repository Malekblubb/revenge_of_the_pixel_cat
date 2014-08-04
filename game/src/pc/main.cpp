//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/core/game.hpp>
#include <pc/core/game_updater.hpp>
#include <pc/core/game_window.hpp>

int main() {
	pc::Game<pc::GameWindow, pc::GameUpdater> game;
	return pc::GameWindow{{400, 400}, "The Revenge of the Pixelcat", game}.run();
}
