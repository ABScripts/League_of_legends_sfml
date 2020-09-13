#include "gamemodel.h"
#include "tank.h"

GameModel::GameModel()
  : mLayers(
            {{Layers::MapLayer, new Entity()},
             {Layers::BattlefieldLayer, new Entity()}
           }),
    mPlayer(new Tank(mLayers[Layers::MapLayer]))
{
}

GameModel::~GameModel()
{
  for (auto & layer : mLayers) {
      delete layer.second;
    }
}

const std::map<GameModel::Layers, Entity *> &GameModel::getLayers() const {
  return mLayers;
}

Tank *GameModel::getPlayer() const
{
  return mPlayer;
}
