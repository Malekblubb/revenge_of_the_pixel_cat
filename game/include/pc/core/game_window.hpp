//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_GAME_WINDOW_HPP
#define PC_CORE_GAME_WINDOW_HPP

#include <pc/common.hpp>

#include <mlk/signals_slots/slot.h>

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
		mlk::slot<> onStop;
		
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
				
				// update
				updateEvents();
				mGameUpdater.runUpdate();
				
				// render
				mRenderWindow.clear();
				mGameUpdater.runRender();				
				mRenderWindow.display();
				
				mGameUpdater.end();
			}
			
			return 0;
		}
		
		void stop() {
			mRunning = false;
			onStop();
		}
		
	private:
		void updateEvents() {
			sf::Event event;
			while(mRenderWindow.pollEvent(event)) {
				switch(event.type) {
					case sf::Event::EventType::Closed: stop(); break;
					case sf::Event::EventType::KeyPressed: break;
					case sf::Event::EventType::KeyReleased: break;
					case sf::Event::EventType::MouseButtonPressed: break;
					case sf::Event::EventType::MouseButtonReleased: break;
					case sf::Event::EventType::MouseWheelMoved: break;
					default: break;
				}
				
				mGame.onEvent(event);
			}
		}
		
		void recreateWindow() {
			mRenderWindow.create(mVideoMode, mTitle, mWindowStyles);
			mNeedRecreate = false;
		}
	};
	
}

#endif // PC_CORE_GAME_WINDOW_HPP 
