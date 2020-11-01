#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System.hpp"
#include <iostream>
#include <memory>
#include <list>

#include <QDebug>

class Command;

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
    void checkNodeCollisions(SceneNode *other, std::vector<std::pair<SceneNode *, SceneNode *> > &collisionPairs);
    void checkSceneCollisions(SceneNode *other, std::vector<std::pair<SceneNode *, SceneNode *> > &collisionPairs);
    virtual void applyCollisionToSelf(SceneNode *) {};
    bool isDestroyed() const;

    virtual float width() const = 0;
    virtual float height() const = 0;
    virtual sf::Vector2f center() const = 0;

protected:
    bool mIsDestroyed = false;


protected:
    sf::Transform getWorldTransform() const;
    virtual sf::FloatRect getBoundingRect() const = 0;

  private:
    SceneNode * mParentNode;
    std::vector<SceneNode*> mChildren; // consider change it to the unique_ptr

  private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final; // implementing sf::Drawable pure virtual function
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    SceneNode & operator=(const SceneNode &);

    friend class QuadTree;
};

#endif //SCENENODE_H
