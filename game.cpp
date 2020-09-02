#include "game.h"
#include <iostream>

AssetManager Game::manager = AssetManager();

Game::Game()
  : mGameWindow(new GameWindow("GameWindow")),
    fps(sf::seconds(1.f / 60.f))
{
}

void Game::run()
{
  //sf::Time currentTime = mClock.restart();

  sf::Time time = sf::Time::Zero;

  while (mGameWindow->isOpen()) {
                 processEvents();
//      sf::Time newTime = mClock.restart();
//      sf::Time frameTime = newTime - currentTime;
//      currentTime = newTime;
//      std::cout << frameTime.asMicroseconds() << std::endl;
//      accumulator += frameTime;

    time += mClock.restart();
     std::cout << time.asSeconds() << std::endl;
      while (time > fps) {

          //std::cout << "   " << accumulator.asMicroseconds() << std::endl;
          update();

          time -= fps;
          render();
      }


    }
}

void Game::update()
{

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
