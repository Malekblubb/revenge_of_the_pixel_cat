//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_GAME_WINDOW_HPP
#define PC_CORE_GAME_WINDOW_HPP

#include "engine_component.hpp"
#include "game_updater.hpp"
#include "input.hpp"
#include <pc/common.hpp>

#include <mlk/signals_slots/slot.h>

namespace pc {
	
	class GameWindow : public EngineComponent {
		sf::RenderWindow mRenderWindow;
		sf::VideoMode mVideoMode;
		std::string mTitle;
		sf::Uint32 mWindowStyles;
		bool mRunning, mNeedRecreate;
		
		Game* mGame{nullptr};
		GameUpdater* mGameUpdater{nullptr};
		Input* mInput{nullptr};
		
	public:
		mlk::slot<> onStop;
		
		GameWindow(sf::VideoMode videoMode, const std::string& title);
		
		virtual void engineInitFinished() override;
		
		int run();
		void stop();

		template<typename... Args>
		void draw(Args&&... args) {
            mRenderWindow.draw(std::forward<Args>(args)...);
        }

        void setTitle(const std::string& title);
		
	private:
		void updateEvents();
		void recreateWindow();
	};
	
}

#endif // PC_CORE_GAME_WINDOW_HPP 
