//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_GAME_MAIN_MENU_HPP
#define PC_GAME_MAIN_MENU_HPP

#include <pc/common.hpp>
#include <pc/core/render_able.hpp>

#include <mlk/time/time.h>
#include "sprite_animator.hpp"

namespace pc {

	class MainMenu : public RenderAble {
		static const GameState mSelfState{GameState::startScreen};

		// start screen
		sf::Sprite mBackground;
		sf::Text mStartText;
		mlk::tm::simple_timer mStartTextTimer{1};
		bool mColorDirection{false};

		EngineT* mEngine{nullptr};
		SpriteAnimator* mSpriteAnimator{nullptr};
		DataManager* mDataManager{nullptr};
		GameWindow* mGameWindow{nullptr};
		Game* mGame{nullptr};

	public:
		void initialize(EngineT* engine, SpriteAnimator* spriteAnimator);

		void update(Fd fd);
		virtual void render(sf::RenderTarget& target) override;
	};

}

#endif // PC_GAME_MAIN_MENU_HPP
