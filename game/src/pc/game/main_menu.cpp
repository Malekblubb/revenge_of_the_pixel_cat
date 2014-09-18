//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/game/main_menu.hpp>
#include <pc/shared/datamanager.hpp>

namespace pc {

	void MainMenu::initialize(EngineT* engine) {
		mEngine = engine;
		mDataManager = engine->getComponent<pc::DataManager>();

		mBackground.setTexture(mDataManager->get<EndingIndex::graphics>("start_background.png"));
		mBackground.setScale(2, 2);
	}

	void MainMenu::render(sf::RenderTarget& target) {
		target.draw(mBackground);
	}

}