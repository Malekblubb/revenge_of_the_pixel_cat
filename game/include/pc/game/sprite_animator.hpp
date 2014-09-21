//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_GAME_SPRITE_ANIMATOR_HPP
#define PC_GAME_SPRITE_ANIMATOR_HPP

#include <pc/common.hpp>
#include <pc/core/render_able.hpp>

#include <mlk/time/time.h>

namespace pc {

	struct SpriteAction {
		sf::Sprite sprite;
		int stepSize{16}, height{16};
		mlk::tm::simple_timer timer{0};
		mlk::slot<sf::Sprite&, Fd> onTimer;
		GameState gameState;

		mlk::ushort textureIndex{0}, maxTextureIndex{1};
		mlk::tm::simple_timer textureTimer{0};
	};

	class SpriteAnimator : public RenderAble {
		std::map<std::string, SpriteAction> mSprites;

		EngineT* mEngine{nullptr};

	public:
		void initialize(EngineT* engine);

		SpriteAction& newSprite(const std::string& name, GameState state);

		void update(Fd fd);
		virtual void render(sf::RenderTarget& target) override;
		void changeTexture(const std::string& name);

		const auto& sprites() const noexcept {return mSprites;}
	};

}

#endif // PC_GAME_SPRITE_ANIMATOR_HPP