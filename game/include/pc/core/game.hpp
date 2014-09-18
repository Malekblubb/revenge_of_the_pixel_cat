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
#include <pc/game/main_menu.hpp>
#include <pc/game/world.hpp>

namespace pc {
	
	class Game : public EngineComponent {
		GameWindow* mGameWindow;
		Input* mInput{nullptr};
		Render* mRender{nullptr};
		DataManager* mDataManager{nullptr};

		MainMenu mMainMenu;
		World mWorld;
		
    public:
		virtual void engineInitFinished() override;
		void run();
		
		void update(Fd fd);
		void render();
		
		void onEvent(const sf::Event& event);

		template<typename Func>
		void registerKey(Key k, Func&& f) {
			mInput->onKey[k] += f;
		}

		template<typename Func>
		void registerButton(Button b, Func&& f) {
			mInput->onButton[b] += f;
		}

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
