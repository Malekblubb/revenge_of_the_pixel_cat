//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_RENDER_HPP
#define PC_CORE_RENDER_HPP

#include "engine_component.hpp"
#include "render_able.hpp"
#include <pc/common.hpp>

namespace pc {
	
	class Render : public EngineComponent {
		std::vector<RenderAble*> mRenderObjects;

		sf::RenderWindow& mRenderWindow;

	public:
		Render(sf::RenderWindow& rw)
				: mRenderWindow{rw} { }

		void add(RenderAble* obj) { mRenderObjects.push_back(obj); }
		
		void renderAll() {
			for(auto& obj : mRenderObjects)
				obj->render(mRenderWindow);
		}

		auto& renderTarget() noexcept { return mRenderWindow; }
	};
	
}

#endif // PC_CORE_RENDER_HPP 
