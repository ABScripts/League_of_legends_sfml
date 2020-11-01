#include "gamemodel.h"
#include "tank.h"

GameModel::GameModel(sf::RenderWindow & window)
  : mLayers(
    {{Layers::MapLayer, new Entity()},
    {Layers::BattlefieldLayer, new Entity()}
    })
  , mPlayer(new Tank(mLayers[Layers::MapLayer], TankModel::TankType::Self, TankModel::TankType::Self, 50, 50))
  , mQuadTree(new QuadTree(0, 0, window.getSize().x, window.getSize().y))
{
 for (int i = 100; i < 500; i += 200) {
  //qDebug() << "SHITTT\n";
  mEnemies.push_back(new Tank(mLayers[Layers::MapLayer], TankModel::TankType::Enemy, TankModel::TankType::Enemy, i + 200, i + 200));
 }

    updateQuadTree(window);
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

void GameModel::updateQuadTree(sf::RenderWindow &window)
{
  sf::Vector2u winRect = window.getSize();

  if (mQuadTree)
    delete mQuadTree;
  mQuadTree = new QuadTree(0, 0, winRect.x, winRect.y);
  for (SceneNode *tank : mEnemies) {
    mQuadTree->insert(tank, window);
    }
  mQuadTree->insert(mPlayer, window);
}

void GameModel::update(sf::RenderWindow &window, std::shared_ptr<std::list<Command*> > playerCommands, const sf::Time &time)
{
  mPlayer->update(time, playerCommands);

  for (auto & layer : mLayers) {
      layer.second->update(time);
    }

  updateQuadTree(window);
}
