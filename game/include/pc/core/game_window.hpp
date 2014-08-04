//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_GAME_WINDOW_HPP
#define PC_CORE_GAME_WINDOW_HPP

#include <pc/common.hpp>

namespace pc {
	
	class GameWindow {
		GameUpdater mGameUpdater;
		sf::RenderWindow mRenderWindow;
		sf::VideoMode mVideoMode;
		std::string mTitle;
		sf::Uint32 mWindowStyles;
		bool mRunning, mNeedRecreate;
		
		TGame& mGame;
		
	public:
		GameWindow(sf::VideoMode videoMode, const std::string& title, TGame& game)
			: mGameUpdater{game}
			, mRenderWindow{videoMode, title}
			, mVideoMode{videoMode}
			, mTitle{title}
			, mWindowStyles{sf::Style::Default}
			, mRunning{false}
			, mNeedRecreate{true}
			, mGame{game} {
			mGame.run(this, &mGameUpdater);
		}
		
		int run() {
			if(mRunning) return 1;
			
			mRunning = true;
			while(mRunning) {
				if(mNeedRecreate) recreateWindow();
				
				mGameUpdater.start();
				mRenderWindow.clear();
				mGameUpdater.runUpdate();
				mGameUpdater.runRender();				
				mRenderWindow.display();
				mGameUpdater.end();
			}
			
			return 0;
		}
		
	private:
		void recreateWindow() {
			mRenderWindow.create(mVideoMode, mTitle, mWindowStyles);
			mNeedRecreate = false;
		}
	};
	
}

#endif // PC_CORE_GAME_WINDOW_HPP 
