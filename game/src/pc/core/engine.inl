//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_ENGINE_INL
#define PC_CORE_ENGINE_INL

#include <pc/core/engine.hpp>
#include <pc/shared/datamanager.hpp>

namespace pc {

	template<typename... EngineComponents>
	void Engine<EngineComponents...>::registerFiles() {
		auto* dataManager(getComponent<pc::DataManager>());
		dataManager->registerFile({"start_background.png", EndingIndex::graphics});
		dataManager->loadAllFiles();
	}

}

#endif // PC_CORE_ENGINE_INL