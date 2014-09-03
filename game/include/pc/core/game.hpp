//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_GAME_HPP
#define PC_CORE_GAME_HPP

#include "engine_component.hpp"
#include <pc/common.hpp>

namespace pc {
	
	class Game : public EngineComponent {
		
	public:
		Game() {
			
		}
		
		virtual void engineInitFinished() override {
			
		}
		
		void run() {
			mlk::lout("pc::Game") << "Running game.";

		}
		
		void update(Fd fd) {
			
		}
		
		void render() {
			
		}
		
		template<typename... Args>
		void renderObject(Args&&... args) {
			
		}
		
		void onEvent(const sf::Event& event) {
			
		}
	};
	
}

#endif // PC_CORE_GAME_HPP
