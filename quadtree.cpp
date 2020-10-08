#include "quadtree.h"

QuadTree::QuadTree(double top, double left, double width, double height)
  : mTreeRect(top, left, width, height)
{
    double halfWidth = width / 2;
    double halfHeight = height / 2;
    mWestNorth->setTreeRect(sf::FloatRect(top, left, halfWidth, halfHeight));
    mNorthEast->setTreeRect(sf::FloatRect(top, left + halfWidth, halfWidth, halfHeight));
    mSouthEast->setTreeRect(sf::FloatRect(top + halfHeight, left + halfWidth, halfWidth, halfHeight));
    mSouthWest->setTreeRect(sf::FloatRect(top + halfHeight, left, halfWidth, halfHeight));
}

bool QuadTree::insert(Entity *node)
{
  if (!contains(*node)) {
      return false;
    }
  else {
      if ( !(mWestNorth->insert(node) ||
             mNorthEast->insert(node) ||
             mSouthEast->insert(node) ||
             mSouthWest->insert(node))) {
           mObjectsIn.push_back(node);
           return true;
      }
    }
}

bool QuadTree::contains(Entity &node) const
{
  sf::FloatRect objectBound = node.getBoundingRect();

  return ((objectBound.top) > (mTreeRect.top) &&
          (objectBound.left) > (objectBound.left) &&
          (objectBound.left + objectBound.width) < (mTreeRect.left + mTreeRect.width) &&
          (objectBound.top + objectBound.height) > (mTreeRect.top + mTreeRect.height));
}

void QuadTree::setTreeRect(const sf::FloatRect &treeRect)
{
  mTreeRect = treeRect;
}
