//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_WORLD_HPP
#define PC_WORLD_HPP

#include "player.hpp"
#include <pc/common.hpp>
#include <pc/core/render.hpp>
#include <pc/core/render_able.hpp>

namespace pc {
	
	class World : public RenderAble {
		Player mPlayer;

		EngineT* mEngine{nullptr};
		Game* mGame{nullptr};

	public:
		const float* mGroundY{nullptr};

		void initialize(EngineT* engine);

		void update(Fd fd);
		virtual void render(sf::RenderTarget& target) override;

		// spawn player, enemies, etc...
		void levelStart();

	private:
		void spawnPlayer();
	};
	
}

#endif // PC_WORLD_HPP 
