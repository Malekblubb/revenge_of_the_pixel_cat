//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_GAME_HPP
#define PC_CORE_GAME_HPP

#include "engine_component.hpp"
#include "game_updater.hpp"
#include <pc/core/input.hpp>
#include <pc/core/render.hpp>
#include <pc/common.hpp>
#include <pc/world.hpp>

namespace pc {
	
	class Game : public EngineComponent {
		Input* mInput{nullptr};
		Render* mRender{nullptr};
		
		World mWorld;
		
    public:
		virtual void engineInitFinished() override;
		void run();
		
		void update(Fd fd);
		void render();
		
		void onEvent(const sf::Event& event);

		// game
		void startLevel();
		void restartLevel();
		void endLevel();

		auto& world() noexcept { return mWorld; }

	private:
		void initialize();
	};
}

#endif // PC_CORE_GAME_HPP
