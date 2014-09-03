//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_ENGINE_COMPONENT_HPP
#define PC_CORE_ENGINE_COMPONENT_HPP

#include <pc/common.hpp>

namespace pc {
	
	class EngineComponent {
	protected:
		EngineT* mEngine;
		
	public:
		void setEngine(EngineT* e) noexcept { mEngine = e; }
		virtual void engineInitFinished() { }
	};
	
}

#endif // PC_CORE_ENGINE_COMPONENT_HPP 
