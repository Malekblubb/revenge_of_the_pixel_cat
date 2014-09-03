//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_ENGINE_HPP
#define PC_ENGINE_HPP

#include <mlk/tools/compiletime.h>

namespace pc {
	
	template<typename... EngineComponents>
	class Engine {
		std::tuple<EngineComponents*...> mComponents;
		
	public:
		template<typename... ComponentArgs>
		Engine(ComponentArgs&&... args)
			: mComponents{std::forward<ComponentArgs>(args)...} {
		}
		
		void initializeAll() {
			mlk::tupleIteration(mComponents, [this](const auto& component) {
				component->setEngine(this);
			});
		}
		
		template<typename ComponentType>
		ComponentType* getComponent() {
			return std::get<mlk::TupleTypeIndex<ComponentType*, decltype(mComponents)>::value>(mComponents);
		}
	};	
}

#endif // PC_ENGINE_HPP 
