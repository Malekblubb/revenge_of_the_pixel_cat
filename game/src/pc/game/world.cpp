//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/game/world.hpp>
#include <pc/core/game.hpp>

namespace pc {

	void World::initialize(EngineT* engine) {
		mEngine = engine;
		mGame = mEngine->getComponent<pc::Game>();


	}

	void World::update(Fd fd) {

	}

	void World::render(sf::RenderTarget& target) {

	}

	void World::levelStart() {
		spawnPlayer();
	}

	void World::spawnPlayer() {

	}
}