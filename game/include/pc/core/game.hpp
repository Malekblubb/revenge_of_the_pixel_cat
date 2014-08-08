//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_GAME_HPP
#define PC_CORE_GAME_HPP

#include "input.hpp"
#include <pc/common.hpp>

namespace pc {
	
	template<typename TGameWindow, typename TGameUpdater>
	class Game {
		TGameWindow* mGameWindow{nullptr};
		TGameUpdater* mGameUpdater{nullptr};
		Input* mInput{nullptr};
		
	public:
		Game() {
			
		}
		
		void run(TGameWindow* window, TGameUpdater* updater) {
			mlk::lout("pc::Game") << "Running game.";
			mGameWindow = window;
			mGameUpdater = updater;
			mInput = &window->input();
			
		}
		
		void update(Fd fd) {
			
		}
		
		void render() {
			
		}
		
		void onEvent(const sf::Event& event) {
			
		}
	};
	
}

#endif // PC_CORE_GAME_HPP
