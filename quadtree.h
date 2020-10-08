#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "entity_system/entity.h"

class QuadTree
{
public:
  QuadTree(double top = 0, double left = 0, double width = 0, double height = 0);
  bool insert(Entity *node);
  bool contains(Entity &node) const;
  void setTreeRect(const sf::FloatRect &treeRect);

private:
  sf::FloatRect mTreeRect;
  std::vector<SceneNode*> mObjectsIn;
  QuadTree * mWestNorth = nullptr;
  QuadTree * mNorthEast = nullptr;
  QuadTree * mSouthWest = nullptr;
  QuadTree * mSouthEast = nullptr;
};

#endif // QUADTREE_H
