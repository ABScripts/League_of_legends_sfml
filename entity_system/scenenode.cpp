#include "scenenode.h"
#include <algorithm>
#include <assert.h>

SceneNode::SceneNode()
  : mParentNode(nullptr)
{

}

SceneNode::~SceneNode() {
  for (auto child : mChildren) {
      delete child;
    }
}

void SceneNode::attachChild(SceneNode *child) {
  child->mParentNode = this;
  mChildren.push_back(std::move(child));
}

void SceneNode::attachToParent(SceneNode *child)
{
  if (mParentNode)
    mParentNode->attachChild(child);
}

SceneNode *SceneNode::detachChild(const SceneNode &node) {
  auto found = std::find_if(mChildren.begin(), mChildren.end(),
                            [&](SceneNode * cnode) -> bool { return cnode == &node; } ); // check whether that node is in children vect
  assert(found != mChildren.end());                                                      // check is it really is there
  SceneNode * result = std::move(*found);                                                // getting that child in an. var
  result->mParentNode = nullptr;
  mChildren.erase(found);                                                                // deleting from this node's children vect
  return result;                                                                         // return it so we could attach that node to some else node
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();

  drawCurrent(target, states);

  for (const auto &child : mChildren) {
      child->draw(target, states);
    }
}

void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

}

void SceneNode::update(const sf::Time &time)
{
  updateCurrent(time);
  for (const auto &child : mChildren) {
      child->update(time);
    }
}

void SceneNode::updateCurrent(const sf::Time &time)
{

}

sf::Transform SceneNode::getWorldTransform() const
{
//  sf::Transform t;
//  t *= getTransform();

//  if (!mChildren.empty()) {
//      for (const auto &child : mChildren) {
//          t *= child->getWorldTransform();
//        }
//    }
  sf::Transform t;
  if (mParentNode->mParentNode) {
      t = mParentNode->getTransform();
    }

  return t * getTransform();
}

void SceneNode::checkNodeCollisions(SceneNode &other, std::vector<std::pair<SceneNode &, SceneNode &> > &collisionPairs, bool &res)
{                                   //layer_
//  if (&other != this) {
//      if (intersects(*this, other)) {                     // check for "main" node
//          collisionPairs.emplace_back(*this, other);
//          res = true;
//        }
//      // check for children
//      for (auto &entityOnLayer : mChildren) { // loop through layer`s children

//            // else, if collision is not detected see for them in deeper "layers"
//            entityOnLayer->checkNodeCollisions(other, collisionPairs, res);
//        }
//    }

    if (&other != this) {
        // check for children
        for (auto &entityOnLayer : other.mChildren) { // loop through layer`s children
            if (entityOnLayer != this) {if (intersects(*this, *entityOnLayer)) {res = true;}
                // else, if collision is not detected see for them in deeper "layers"
                this->checkNodeCollisions(*entityOnLayer, collisionPairs, res);}

          }
      }
}

void SceneNode::checkSceneCollisions(SceneNode &other, std::vector<std::pair<SceneNode &, SceneNode &> > &collisionPairs, bool &res) {
  checkNodeCollisions(other, collisionPairs, res);

  for (auto &entityOnLayer : other.mChildren) {
      checkNodeCollisions(*entityOnLayer, collisionPairs, res);
    }
}

bool SceneNode::intersects(const SceneNode &lhr, const SceneNode &rhs)
{
  return lhr.getBoundingRect().intersects(rhs.getBoundingRect());
}
