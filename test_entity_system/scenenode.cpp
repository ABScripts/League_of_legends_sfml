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
