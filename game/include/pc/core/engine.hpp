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
		using TupleType = decltype(mComponents);
		
	public:
		template<typename... ComponentArgs>
		Engine(ComponentArgs&&... args)
			: mComponents{std::forward<ComponentArgs>(args)...} {
		}
		
		void initializeAll() {
			// set the engine to all components
			mlk::tupleIteration(mComponents, [this](const auto& component) {
				component->setEngine(this);
			});
			
			// tell the components that they can use all other components
			mlk::tupleIteration(mComponents, [](const auto& component) {
				component->engineInitFinished();
			});
		}
		
		template<typename ComponentType>
		ComponentType* getComponent() {
			return std::get<mlk::TupleTypeIndex<ComponentType*, TupleType>::value>(mComponents);
		}
		
		template<typename ForwardedType>
		struct GetComponentType {
			using type = typename std::tuple_element<mlk::TupleTypeIndex<ForwardedType*, TupleType>::value, TupleType>::type;
		};
	};	
}

#endif // PC_ENGINE_HPP 
