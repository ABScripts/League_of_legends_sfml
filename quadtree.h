#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "entity_system/entity.h"
#include "SFML/Graphics.hpp"

class QuadTree
{
public:
  QuadTree(double x = 0, double y = 0, double width = 0, double height = 0, unsigned level = 1);
  ~QuadTree();
  void insert(SceneNode *node, sf::RenderWindow &window);
  void retrieve(std::vector<SceneNode*> &gameObjectInQuadrant, SceneNode *gameObject) const;
  void getGameObjectsByTreeLayers(std::vector<std::vector<SceneNode *> > &) const;

private:
  static unsigned MAX_LEVEL;

  enum class Quadrant {
    NO_QUADRANT = -1, // should start from -1 for correct interpretation of those values as the int ones.
    TOP_LEFT_QUADRANT = 0,
    TOP_RIGHT_QUADRANT,
    BOTTOM_LEFT_QUADRANT,
    BOTTOM_RIGHT_QUADRANT
  };

  sf::FloatRect mTreeRect;
  std::vector<SceneNode*> mObjectsIn;
  std::vector<QuadTree*> mNodes;
  unsigned mLevel;

  // test code
  std::vector<sf::RectangleShape*> mRects;
  //end test code

private:
  void deallocate(); // deletes quadtree hierarchy
  void subdivide();  // create new four sub quadtrees
  Quadrant getQuadrant(const SceneNode *node) const;
  bool hasChildren() const;
};

#endif // QUADTREE_H
