#include <iostream>
#include "SFML/Graphics.hpp"
#include "assetmanager.h"
#include "gamewindow.h"
#include "inputhandle.h"

#include "tank.h"

using namespace std;

int main()
{
  AssetManager manager;
  GameWindow gameWindow("GameWindow");
  sf::Event event;
  while (gameWindow.isOpen()) {

      while(gameWindow.pollEvent(gameWindow.event())) {
          if (gameWindow.event().type == sf::Event::EventType::Closed) {

              gameWindow.close();
            }
        }

      gameWindow.clear(sf::Color::White);
      gameWindow.handleInput();
      gameWindow.render();
      gameWindow.display();
    }
}
