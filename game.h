#ifndef GAME_H
#define GAME_H

#include <memory>
#include "gamewindow.h"
#include "assetmanager.h"

class Game
{
public:
  Game();
  void run();
private:
  std::unique_ptr<GameWindow> mGameWindow;
  static AssetManager manager;
  sf::Clock mClock;
  const sf::Time fps;
private:
  void update();
  void render();
  void processEvents();
};

#endif // GAME_H
