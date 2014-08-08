//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_GAME_WINDOW_HPP
#define PC_CORE_GAME_WINDOW_HPP

#include "input.hpp"
#include <pc/common.hpp>

#include <mlk/signals_slots/slot.h>

namespace pc {
	
	class GameWindow {
		sf::RenderWindow mRenderWindow;
		sf::VideoMode mVideoMode;
		std::string mTitle;
		sf::Uint32 mWindowStyles;
		bool mRunning, mNeedRecreate;
		
		GameUpdater mGameUpdater;
		Input mInput;
		
		TGame& mGame;
		
	public:
		mlk::slot<> onStop;
		
		GameWindow(sf::VideoMode videoMode, const std::string& title, TGame& game)
			: mRenderWindow{videoMode, title}
			, mVideoMode{videoMode}
			, mTitle{title}
			, mWindowStyles{sf::Style::Default}
			, mRunning{false}
			, mNeedRecreate{true}
			, mGameUpdater{game}
			, mGame{game} {	}
		
		int run() {
			if(mRunning) return 1;
			
			mlk::lout("pc::GameWindow", true) << "Running gamewindow.";
			mGame.run(this, &mGameUpdater);
			mRunning = true;
			while(mRunning) {
				if(mNeedRecreate) recreateWindow();
				if(!mRenderWindow.isOpen()) {
					stop();
					mlk::lerr() << "Something went wrong during window (re)creation. Stopping.";
				}
				
				mGameUpdater.start();
				
				// update
				mInput.update(mRenderWindow.mapPixelToCoords(sf::Mouse::getPosition(mRenderWindow)));
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
			mlk::lout("pc::GameWindow") << "Stopping gamewindow.";
		}
		
		Input& input() noexcept { return mInput; }
		
	private:
		void updateEvents() {
			sf::Event event;
			while(mRenderWindow.pollEvent(event)) {
				switch(event.type) {
					case sf::Event::EventType::Closed: stop(); break;
					case sf::Event::EventType::KeyPressed: mInput.keyPressed(event.key.code);  break;
					case sf::Event::EventType::KeyReleased: mInput.keyReleased(event.key.code);  break;
					case sf::Event::EventType::MouseButtonPressed: mInput.mousePressed(event.mouseButton.button);  break;
					case sf::Event::EventType::MouseButtonReleased: mInput.mouseReleased(event.mouseButton.button);  break;
					case sf::Event::EventType::MouseWheelMoved: mInput.mouseScrolled(event.mouseWheel.delta);  break;
					default: break;
				}
				
				mGame.onEvent(event);
			}
		}
		
		void recreateWindow() {
			mRenderWindow.close();
			mRenderWindow.create(mVideoMode, mTitle, mWindowStyles);
			mNeedRecreate = false;
			mlk::lout("pc::GameWindow") << "Windowstatus after (re)creation; isOpen(): " << std::boolalpha << mRenderWindow.isOpen();
		}
	};
	
}

#endif // PC_CORE_GAME_WINDOW_HPP 
