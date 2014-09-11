//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/core/game.hpp>
#include <pc/core/game_window.hpp>

namespace pc {

    GameWindow::GameWindow(sf::VideoMode videoMode, const std::string &title)
            : mRenderWindow{videoMode, title}
            , mVideoMode{videoMode}
            , mTitle{title}
            , mWindowStyles{sf::Style::Default}
            , mRunning{false}
            , mNeedRecreate{true} { }

    void GameWindow::engineInitFinished() {
        mGame = mEngine->getComponent<Game>();
        mGameUpdater = mEngine->getComponent<GameUpdater>();
        mInput = mEngine->getComponent<Input>();
    }

    int GameWindow::run() {
        if (mRunning) return 1;

        mlk::lout("pc::GameWindow", true) << "Running gamewindow.";
        mGame->run();
        mRunning = true;
        while (mRunning) {
            if (mNeedRecreate) recreateWindow();
            if (!mRenderWindow.isOpen()) {
                stop();
                mlk::lerr() << "Something went wrong during window (re)creation. Stopping.";
            }

            mGameUpdater->start();

            // update
            mInput->update(mRenderWindow.mapPixelToCoords(sf::Mouse::getPosition(mRenderWindow)));
            updateEvents();
            mGameUpdater->runUpdate();

            // render
            mRenderWindow.clear();
            mGameUpdater->runRender();
            mRenderWindow.display();

            mGameUpdater->end();
        }

        return 0;
    }

    void GameWindow::stop() {
        mRunning = false;
        onStop();
        mlk::lout("pc::GameWindow") << "Stopping gamewindow.";
    }

    void GameWindow::updateEvents() {
        sf::Event event;
        while(mRenderWindow.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::EventType::Closed: stop(); break;
                case sf::Event::EventType::KeyPressed: mInput->keyPressed(event.key.code);  break;
                case sf::Event::EventType::KeyReleased: mInput->keyReleased(event.key.code);  break;
                case sf::Event::EventType::MouseButtonPressed: mInput->mousePressed(event.mouseButton.button);  break;
                case sf::Event::EventType::MouseButtonReleased: mInput->mouseReleased(event.mouseButton.button);  break;
                case sf::Event::EventType::MouseWheelMoved: mInput->mouseScrolled(event.mouseWheel.delta);  break;
                default: break;
            }

            mGame->onEvent(event);
        }
    }

    void GameWindow::recreateWindow() {
        mRenderWindow.close();
        mRenderWindow.create(mVideoMode, mTitle, mWindowStyles);
        mNeedRecreate = false;
        mlk::lout("pc::GameWindow") << "Windowstatus after (re)creation; isOpen(): " << std::boolalpha << mRenderWindow.isOpen();
    }

    void GameWindow::setTitle(const std::string& title) {
        mTitle = title;
        mRenderWindow.setTitle(mTitle);
    }
}