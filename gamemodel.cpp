#include "gamemodel.h"
#include "tank.h"

GameModel::GameModel(sf::Rect<double> winRect, sf::RenderWindow & window)
  : mLayers(
    {{Layers::MapLayer, new Entity()},
    {Layers::BattlefieldLayer, new Entity()}
    })
  , mPlayer(new Tank(mLayers[Layers::MapLayer]))
  , mWindowRect(winRect)
  , mQuadTree(new QuadTree(winRect.left, winRect.top, winRect.width, winRect.height))
{
//  for (int i = 100; i < 1000; i += 100) {
    mEnemies.push_back(new Tank(mLayers[Layers::MapLayer], TankModel::TankType::Enemy, TankModel::TankType::Enemy, 600, 500));
  //}

  update(window);
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

void GameModel::retrieve(std::vector<SceneNode *> &nd, SceneNode *node)
{
  mQuadTree->retrieve(nd, node);
}

void GameModel::insertInQuadTree(SceneNode *node, sf::RenderWindow &window)
{
  mQuadTree->insert(node, window);
}

void GameModel::getGameObjectsByTreeLayers(std::vector<std::vector<SceneNode *> > &gameObjectByLayers) const
{
  mQuadTree->getGameObjectsByTreeLayers(gameObjectByLayers);
}

void GameModel::update(sf::RenderWindow &window)
{
  if (mQuadTree)
    delete mQuadTree; // delete old one and then create brand new
  mQuadTree = new QuadTree(mWindowRect.left, mWindowRect.top, mWindowRect.width, mWindowRect.height);
  // forming the quad tree structure
  for (SceneNode *tank : mEnemies) {
    mQuadTree->insert(tank, window);
    }
  mQuadTree->insert(mPlayer, window);
  // end forming the quad tree structure
}
