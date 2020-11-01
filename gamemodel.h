#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <vector>
#include <map>
#include "SFML/Graphics/Rect.hpp"
#include "quadtree.h"

class Tank;
class Entity;
class SceneNode;

class GameModel
{
public:
  enum class Layers {
    MapLayer = 0,
    BattlefieldLayer
  };

  GameModel(sf::RenderWindow & window);
  ~GameModel();
  const std::map<Layers, Entity *> &getLayers() const;
  void update(sf::RenderWindow &window, std::shared_ptr<std::list<Command *> > playerCommands, const sf::Time &time);
  // functions to work with a quad tree
  void retrieve(std::vector<SceneNode*> &nd, SceneNode *node);
  void insertInQuadTree(SceneNode *node, sf::RenderWindow &window);
  void getGameObjectsByTreeLayers(std::vector< std::vector<SceneNode*> > &gameObjectByLayers) const;

private:
  std::map<Layers, Entity*> mLayers;
  Tank * mPlayer;
  std::vector<SceneNode *> mEnemies;
  QuadTree *mQuadTree;

private:
  void updateQuadTree(sf::RenderWindow &window);
};

#endif // GAMEMODEL_H
