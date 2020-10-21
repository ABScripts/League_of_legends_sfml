#include "quadtree.h"
#include <QDebug>

unsigned QuadTree::MAX_LEVEL = 5;

QuadTree::QuadTree(double x, double y, double width, double height, unsigned level)
  : mTreeRect(x, y, width, height)
  , mLevel(++level)
{

}

QuadTree::~QuadTree()
{
  deallocate();
}

/*
If current quadtree has some children than try to insert current node in already existed one.
Else if no children quad trees are availaible than push the node, loop throughall the entities inserted in current tree.
If some of the entities moved to another tree node than delete them from the current one and insert forward.
*/
void QuadTree::insert(SceneNode *node, sf::RenderWindow &window)
{
  if (hasChildren()) {
    Quadrant quadrant = getQuadrant(node);
    if (quadrant != Quadrant::NO_QUADRANT) {
        mNodes[static_cast<int>(quadrant)]->insert(node, window);
        return;
      }
    }

  if (mLevel >= MAX_LEVEL) return;
  subdivide();

  mObjectsIn.push_back(node);

  SceneNode * currentGameObject = nullptr;
  for (std::vector<SceneNode*>::iterator gameObject = mObjectsIn.begin(); gameObject != mObjectsIn.end(); ) {
      Quadrant quadrant = getQuadrant(*gameObject);
      if (quadrant != Quadrant::NO_QUADRANT) {
        currentGameObject = *gameObject;
        mObjectsIn.erase(gameObject);
        mNodes[static_cast<int>(quadrant)]->insert(currentGameObject, window);
        }
      else {
          ++gameObject;
        }
    }
}

// get the object and return a bunch of other objects which are in the one square with that one
void QuadTree::retrieve(std::vector<SceneNode*> &gameObjectsInQuadrant, SceneNode *gameObject) const
{
  Quadrant quadrant = getQuadrant(gameObject);
  if (quadrant != Quadrant::NO_QUADRANT && hasChildren()) {
      mNodes[static_cast<int>(quadrant)]->retrieve(gameObjectsInQuadrant, gameObject);
  }
  for (auto* gameObject : mObjectsIn) {
      gameObjectsInQuadrant.push_back(gameObject);
    }
}

/*
Return a vector of vectors which contains all the game objects in each quadrant
*/
void QuadTree::getGameObjectsByTreeLayers(std::vector<std::vector<SceneNode *> > &gameObjectsByLayers) const
{
  if (hasChildren())
    for (auto & node : mNodes) {
      if (node->hasChildren()) {
          node->getGameObjectsByTreeLayers(gameObjectsByLayers);
        }
      }

  if (!mObjectsIn.empty()) {
      std::vector<SceneNode *> objectsInNode;
      for (auto & gameObject : mObjectsIn) {
             objectsInNode.push_back(gameObject);
        }
      gameObjectsByLayers.push_back(objectsInNode);
    }
}

QuadTree::Quadrant QuadTree::getQuadrant(const SceneNode *gameObject) const
{
  Quadrant quadrant = Quadrant::NO_QUADRANT;
  sf::FloatRect gameObjectRect = gameObject->getBoundingRect();
  sf::Vector2<double> middlePoint = {mTreeRect.left + mTreeRect.width / 2,
                                     mTreeRect.top + mTreeRect.height / 2};

  bool somewhereInTopQuadrant = (gameObjectRect.top + gameObjectRect.height) < middlePoint.y;
  bool somewhereInBottomQuadrant = gameObjectRect.top > middlePoint.y;

  if (gameObjectRect.left + gameObjectRect.width < middlePoint.x) {
      if (somewhereInTopQuadrant) {
          quadrant = Quadrant::TOP_LEFT_QUADRANT;
        }
      else if (somewhereInBottomQuadrant) {
          quadrant = Quadrant::BOTTOM_LEFT_QUADRANT;
        }
    }
  else if (gameObjectRect.left > middlePoint.x) {
      if (somewhereInTopQuadrant) {
          quadrant = Quadrant::TOP_RIGHT_QUADRANT;
        }
      else if (somewhereInBottomQuadrant) {
          quadrant = Quadrant::BOTTOM_RIGHT_QUADRANT;
        }
    }

  return quadrant;
}

bool QuadTree::hasChildren() const
{
  return !mNodes.empty();
}

void QuadTree::deallocate()
{
  for (auto & node : mNodes) {
      node->deallocate();
    }
  mObjectsIn.clear();
  for (std::vector<sf::RectangleShape*>::iterator it = mRects.begin(); it != mRects.end(); ++it) {
     mRects.erase(it);
    }
}

/*
TOP_LEFT     |   TOP_RIGHT
------------MID---------------
BOTTOM_LEFT  |   BOTTOM_RIGHT
*/

void QuadTree::subdivide()
{
  double halfWidth = mTreeRect.width / 2;
  double halfHeight = mTreeRect.height / 2;
  double x = mTreeRect.left;
  double y = mTreeRect.top;
  mNodes.push_back(new QuadTree(x, y, halfWidth, halfHeight, mLevel));                              // TOP_LEFT
  mNodes.push_back(new QuadTree(x + halfWidth, y, halfWidth, halfHeight, mLevel));                  // TOP_RIGHT
  mNodes.push_back(new QuadTree(x, y + halfHeight, halfWidth, halfHeight, mLevel));                 // BOTTOM_LEFT
  mNodes.push_back(new QuadTree(x + halfWidth, y + halfHeight, halfWidth, halfHeight, mLevel));    // BOTTOM_RIGHT
}
