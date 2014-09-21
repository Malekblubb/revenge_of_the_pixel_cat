//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/core/game.hpp>
#include <pc/game/sprite_animator.hpp>

namespace pc {

	void SpriteAnimator::initialize(EngineT* engine) {
		mEngine = engine;
	}

	SpriteAction& SpriteAnimator::newSprite(const std::string& name, GameState state) {
		mSprites[name] = {};
		auto& sa(mSprites[name]);
		sa.gameState = state;
		sa.sprite.setTextureRect({0, 0, sa.stepSize, sa.height});
		return sa;
	}

	void SpriteAnimator::render(sf::RenderTarget& target) {
		for(const auto& sprite : mSprites)
			if(mEngine->getComponent<pc::Game>()->isGameState(sprite.second.gameState))
				target.draw(sprite.second.sprite);
	}

	void SpriteAnimator::update(Fd fd) {
		for(auto& sa : mSprites) {
			if(sa.second.timer.timed_out()) {
				sa.second.onTimer(sa.second.sprite, fd);
				sa.second.timer.restart();
			}
			if(sa.second.textureTimer.timed_out()) {
				changeTexture(sa.first);
				sa.second.textureTimer.restart();
			}
		}
	}

	void SpriteAnimator::changeTexture(const std::string& name) {
		auto& s(mSprites[name]);
		s.sprite.setTextureRect({s.stepSize * s.textureIndex, 0, s.stepSize, s.height});

		if(s.textureIndex == s.maxTextureIndex)
			s.textureIndex = 0;
		else ++s.textureIndex;
	}
}