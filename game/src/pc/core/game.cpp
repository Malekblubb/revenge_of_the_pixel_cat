//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/core/game.hpp>
#include <pc/core/game_window.hpp>

namespace pc {

    void Game::engineInitFinished() {
		initialize();
    }

	void Game::initialize() {
		// set up all needed components
		mInput = mEngine->getComponent<pc::Input>();
		mRender = mEngine->getComponent<pc::Render>();

		mWorld.mEngine = mEngine;

		mRender->add(&mWorld);

		// add standard input
		mInput->onKey[Key::A] = [this]{ startLevel(); };
	}


    void Game::run() {
        mlk::lout("pc::Game") << "Running game.";
    }

    void Game::update(Fd fd) {
        mEngine->getComponent<pc::GameWindow>()->setTitle(std::to_string(mEngine->getComponent<pc::GameUpdater>()->fps()));
    }

    void Game::render() {
        mRender->renderAll();
    }

    void Game::onEvent(const sf::Event &event) {

    }


	void Game::startLevel() {
		mWorld.levelStart();
	}

	void Game::restartLevel() {

	}

	void Game::endLevel() {

	}
}