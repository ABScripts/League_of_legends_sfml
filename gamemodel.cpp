#include "gamemodel.h"
#include "tank.h"

GameModel::GameModel()
  : mLayers(
            {{Layers::MapLayer, new Entity()},
             {Layers::BattlefieldLayer, new Entity()}
           }),
    mPlayer(new Tank(mLayers[Layers::MapLayer]))
{
  for (int i = 100; i < 1000; i += 100)
    mEnemies.push_back(new Tank(mLayers[Layers::MapLayer], TankModel::TankType::Enemy, TankModel::TankType::Enemy, i, i));
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

const std::vector<SceneNode *> &GameModel::getEnemies() const
{
  return mEnemies;
}
