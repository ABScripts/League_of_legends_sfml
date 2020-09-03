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
  static const sf::Time mFps;
  static AssetManager mManager;
  static sf::Color mRefreshColor;
  std::unique_ptr<GameWindow> mGameWindow;
  sf::Clock mClock;
private:
  void update(const sf::Time &);
  void render();
  void processEvents();
};

#endif // GAME_H
