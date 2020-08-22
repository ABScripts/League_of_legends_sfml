#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"

class SceneNode : public sf::Drawable, public sf::Transformable{
  public:
    SceneNode();
    ~SceneNode();
    SceneNode & operator=(const SceneNode &) = delete;
    SceneNode(const SceneNode&) = delete;
    void attachChild(SceneNode * child);
    SceneNode *detachChild(const SceneNode &node);
  private:
    SceneNode * mParentNode;
    std::vector<SceneNode*> mChildren; // consider change it to the unique_ptr
  private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final; // implementing sf::Drawable pure virtual function
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif //SCENENODE_H
