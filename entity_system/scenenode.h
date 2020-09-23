#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System.hpp"
#include <iostream>

namespace sf {
  class Sprite;
}

class SceneNode : public sf::Drawable, public sf::Transformable{
  public:
    static bool intersects(const SceneNode & lhr, const SceneNode & rhs);
  public:
    SceneNode();
    ~SceneNode();
    void attachChild(SceneNode * child);
    void attachToParent(SceneNode * child);
    SceneNode *detachChild(const SceneNode &node);
    virtual void update(const sf::Time & time);
    virtual void updateCurrent(const sf::Time & time);
    sf::Transform getWorldTransform() const;
    void checkNodeCollisions(SceneNode &other, std::vector<std::pair<SceneNode&, SceneNode&> > &collisionPairs, bool &res);
    void checkSceneCollisions(SceneNode &other, std::vector<std::pair<SceneNode &, SceneNode &> > &collisionPairs, bool &res);
  private:
    SceneNode * mParentNode;
    std::vector<SceneNode*> mChildren; // consider change it to the unique_ptr
  private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final; // implementing sf::Drawable pure virtual function
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual sf::FloatRect getBoundingRect() const = 0;
    SceneNode & operator=(const SceneNode &);
    //SceneNode(const SceneNode &); // resolve this problem
};

#endif //SCENENODE_H
