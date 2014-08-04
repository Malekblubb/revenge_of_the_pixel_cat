//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_GAME_HPP
#define PC_CORE_GAME_HPP

#include <pc/common.hpp>

namespace pc {
	
	template<typename TGameWindow, typename TGameUpdater>
	class Game {
		TGameWindow* mGameWindow{nullptr};
		TGameUpdater* mGameUpdater{nullptr};
		
	public:
		Game() {
			
		}
		
		void run(TGameWindow* window, TGameUpdater* updater) {
			mGameWindow = window;
			mGameUpdater = updater;
		}
		
		void update(Fd fd) {
			MD("update");
		}
		
		void render() {
			MD("render");
		}
	};
	
}

#endif // PC_CORE_GAME_HPP
