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

  GameModel(sf::Rect<double> winRect,  sf::RenderWindow & window);
  ~GameModel();
  const std::map<Layers, Entity *> &getLayers() const;
  Tank *getPlayer() const;
  const std::vector<SceneNode *> &getEnemies() const;
  void update(sf::RenderWindow &window);
  // functions to work with a quad tree
  void retrieve(std::vector<SceneNode*> &nd, SceneNode *node);
  void insertInQuadTree(SceneNode *node, sf::RenderWindow &window);
  void getGameObjectsByTreeLayers(std::vector< std::vector<SceneNode*> > &gameObjectByLayers) const;

private:
    // temp var
  sf::Rect<double> mWindowRect;
  // game layers -> defines their childrens` render level
  std::map<Layers, Entity*> mLayers;
  Tank * mPlayer;
  std::vector<SceneNode *> mEnemies;
  QuadTree *mQuadTree;

//  std::vector<std::pair<SceneNode &, SceneNode&> > mCollisionPairs;
};

#endif // GAMEMODEL_H
