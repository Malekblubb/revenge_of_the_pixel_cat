//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_GAME_MAIN_MENU_HPP
#define PC_GAME_MAIN_MENU_HPP

#include <pc/common.hpp>
#include <pc/core/render_able.hpp>

namespace pc {

	class MainMenu : public RenderAble {
		// start background
		sf::Sprite mBackground;

		EngineT* mEngine{nullptr};
		DataManager* mDataManager{nullptr};

	public:
		void initialize(EngineT* engine);

		virtual void render(sf::RenderTarget& target) override;
	};

}

#endif // PC_GAME_MAIN_MENU_HPP
