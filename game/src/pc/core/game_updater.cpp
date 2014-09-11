//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/core/game.hpp>
#include <pc/core/game_updater.hpp>

namespace pc {

    void GameUpdater::engineInitFinished() {
        mGame = mEngine->getComponent<Game>();
    }

	void GameUpdater::runUpdate() {
		mCurrentCut += mFrameduration;
		for(; mCurrentCut >= mNextCut; mCurrentCut -= mNextCut)
			mGame->update(mStep);
	}
	
	void GameUpdater::runRender() {
		mGame->render();
	}

    void GameUpdater::start() noexcept {
        mLastUpdate = mlk::tm::time_pnt();
    }

    void GameUpdater::end() noexcept {
        mFrameduration = mlk::tm::duration_to_now_as<float>(mLastUpdate);
    }
}
