//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/core/game.hpp>
#include <pc/core/game_window.hpp>
#include <pc/shared/datamanager.hpp>

namespace pc {

    void Game::engineInitFinished() {
		initialize();
    }

	void Game::initialize() {
		// set up all needed components
		mGameWindow = mEngine->getComponent<pc::GameWindow>();
		mInput = mEngine->getComponent<pc::Input>();
		mRender = mEngine->getComponent<pc::Render>();
		mDataManager = mEngine->getComponent<pc::DataManager>();

		// initialize other stuff
		mMainMenu.initialize(mEngine, &mSpriteAnimator);
		mSpriteAnimator.initialize(mEngine);
		mWorld.initialize(mEngine);

		// add all render objects in the right order
		mRender->add(&mMainMenu);
		mRender->add(&mWorld);
		mRender->add(&mSpriteAnimator);

		// add standard input
		registerKey(Key::Escape, [this]{ mGameWindow->stop(); });
//		registerKey(Key::A, [this]{ startLevel(); });
	}


    void Game::run() {
        mlk::lout("pc::Game") << "Running game.";
    }

    void Game::update(Fd fd) {
        mEngine->getComponent<pc::GameWindow>()->setTitle(std::to_string(mEngine->getComponent<pc::GameUpdater>()->fps()));

		mMainMenu.update(fd);
		mSpriteAnimator.update(fd);
		mWorld.update(fd);
    }

    void Game::render() {
        mRender->renderAll();
    }

    void Game::onEvent(const sf::Event& event) {

    }


	void Game::startLevel() {


		mWorld.levelStart();
	}

	void Game::restartLevel() {

	}

	void Game::endLevel() {

	}
}