#include "game.h"
#include <iostream>

const sf::Time Game::mFps = sf::seconds(1.f / 60.f);
AssetManager Game::mManager = AssetManager();
sf::Color Game::mRefreshColor = sf::Color::White;

Game::Game()
  : mGameWindow(new GameWindow("GameWindow"))
{
}

void Game::run()
{
  sf::Time time = sf::Time::Zero;

  while (mGameWindow->isOpen()) {
      processEvents();
      time += mClock.restart();

      for ( ; time > mFps; time -= mFps) {
          update(mFps);
          render();
      }
    }
}

void Game::update(const sf::Time &time)
{
  mGameWindow->update(time);
}

void Game::render()
{
  mGameWindow->clear(sf::Color::White);
  mGameWindow->render();
  mGameWindow->display();
}

void Game::processEvents()
{
  while(mGameWindow->eventsHaveHappened()) {
      if (mGameWindow->event().type == sf::Event::EventType::Closed) {
          mGameWindow->close();
        }
    }

  mGameWindow->handleInput();
}
