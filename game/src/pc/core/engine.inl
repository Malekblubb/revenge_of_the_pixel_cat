//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

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