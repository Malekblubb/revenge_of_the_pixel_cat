//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/core/game_window.hpp>
#include <pc/game/main_menu.hpp>
#include <pc/game/sprite_animator.hpp>
#include <pc/shared/datamanager.hpp>
#include <pc/core/game.hpp>

namespace pc {

	void MainMenu::initialize(EngineT* engine, SpriteAnimator* spriteAnimator) {
		mEngine = engine;
		mSpriteAnimator = spriteAnimator;
		mDataManager = engine->getComponent<pc::DataManager>();
		mGameWindow = engine->getComponent<pc::GameWindow>();
		mGame = engine->getComponent<pc::Game>();

		mBackground.setTexture(mDataManager->get<EndingIndex::graphics>("start_background.png"));
		mBackground.setScale(2, 2);


		mStartText.setFont(mDataManager->get<EndingIndex::font>("uni0553.ttf"));
		mStartText.setString("Press Start!");
		mStartText.setCharacterSize(40);
		mStartText.setPosition(640, 360);
		mStartText.setColor(fromHex("#ff0000"));
		mStartTextTimer.run();

		auto& s(mSpriteAnimator->newSprite("bird0", mSelfState));
		s.sprite.setTexture(mDataManager->get<EndingIndex::graphics>("bird_anim.png"));
		s.timer.restart(500);
		s.textureTimer.restart(1000);
		s.onTimer += [this](sf::Sprite& sprite, Fd fd) {
			sprite.move(Vec2f{5.f, 0.f} * fd);
			if(sprite.getPosition().x > static_cast<float>(mGameWindow->renderWindow().getSize().x))
				sprite.setPosition(0.f, 0.f);
		};

		auto& s2(mSpriteAnimator->newSprite("bird1", mSelfState));
		s2.sprite.setTexture(mDataManager->get<EndingIndex::graphics>("bird_anim.png"));
		s2.sprite.setPosition(0.f, 50.f);
		s2.timer.restart(100);
		s2.textureTimer.restart(200);
		s2.onTimer += [this](sf::Sprite& sprite, Fd fd) {
			sprite.move(Vec2f{5.f, 0.f} * fd);
			if(sprite.getPosition().x > static_cast<float>(mGameWindow->renderWindow().getSize().x))
				sprite.setPosition(0.f, 50.f);
		};

		auto& s3(mSpriteAnimator->newSprite("bird2", mSelfState));
		s3.sprite.setTexture(mDataManager->get<EndingIndex::graphics>("bird_anim.png"));
		s3.sprite.setPosition(static_cast<float>(mGameWindow->renderWindow().getSize().x), 80.f);
		s3.timer.restart(300);
		s3.textureTimer.restart(600);
		s3.onTimer += [this](sf::Sprite& sprite, Fd fd) {
			sprite.move(Vec2f{-4.f, 0.f} * fd);
			if(sprite.getPosition().x < 0.f)
				sprite.setPosition(static_cast<float>(mGameWindow->renderWindow().getSize().x), 80.f);
		};

		auto& s4(mSpriteAnimator->newSprite("bird3", mSelfState));
		s4.sprite.setTexture(mDataManager->get<EndingIndex::graphics>("bird_anim.png"));
		s4.sprite.setPosition(static_cast<float>(mGameWindow->renderWindow().getSize().x), 120.f);
		s4.timer.restart(200);
		s4.textureTimer.restart(400);
		s4.onTimer += [this](sf::Sprite& sprite, Fd fd) {
			sprite.move(Vec2f{-6.f, 0.f} * fd);
			if(sprite.getPosition().x < 0.f)
				sprite.setPosition(static_cast<float>(mGameWindow->renderWindow().getSize().x), 120.f);
		};
	}

	void MainMenu::update(Fd fd) {
		// animate the start text
		if(mStartTextTimer.timed_out()) {
			auto oldColor(mStartText.getColor());
			if(oldColor.r == 255) mColorDirection = false;
			else if(oldColor.r == 0) mColorDirection = true;
			mStartText.setColor({mColorDirection ? ++oldColor.r : --oldColor.r, oldColor.g, oldColor.b});
			mStartTextTimer.restart();
		}
	}

	void MainMenu::render(sf::RenderTarget& target) {
		if(!mGame->isGameState(GameState::startScreen))
			return;

		target.draw(mBackground);
		target.draw(mStartText);

	}

}