//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_ENGINE_HPP
#define PC_ENGINE_HPP

#include <mlk/log/log.h>
#include <mlk/time/time_utl.h>
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
			auto start(mlk::tm::time_pnt());

			// set the engine to all components
			mlk::tupleIteration(mComponents, [this](const auto& component, auto) {
				component->setEngine(this);
			});

			// do other engine work
			registerFiles();

			// tell the components that they can use all other components
			mlk::tupleIteration(mComponents, [](const auto& component, auto) {
				component->engineInitFinished();
			});

			auto duration(mlk::tm::duration_to_now_as<float>(start));
			mlk::lout("pc::Engine") << "Engine initialisation finished after " << duration << " ms";
		}
		
		template<typename ComponentType>
		ComponentType* getComponent() {
			return std::get<mlk::TupleTypeIndex<ComponentType*, TupleType>::value>(mComponents);
		}
		
		template<typename ForwardedType>
		struct GetComponentType {
			using type = typename std::tuple_element<mlk::TupleTypeIndex<ForwardedType*, TupleType>::value,
					TupleType>::type;
		};


		// engine work
		void registerFiles();
	};
}

#endif // PC_ENGINE_HPP 
