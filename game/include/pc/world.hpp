//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_WORLD_HPP
#define PC_WORLD_HPP

#include "common.hpp"
#include <pc/core/render.hpp>
#include <pc/core/render_able.hpp>

namespace pc {
	
	class World : public RenderAble {
	public:
		EngineT* mEngine{nullptr};
		
		virtual void render() override;

		// spawn player, enemies, etc...
		void levelStart();

	private:
		void spawnPlayer();
	};
	
}

#endif // PC_WORLD_HPP 
