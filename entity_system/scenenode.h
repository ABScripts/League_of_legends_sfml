#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System.hpp"

class SceneNode : public sf::Drawable, public sf::Transformable{
  public:
    SceneNode();
    ~SceneNode();
    void attachChild(SceneNode * child);
    void attachToParent(SceneNode * child);
    SceneNode *detachChild(const SceneNode &node);
    virtual void update(const sf::Time & time);
    virtual void updateCurrent(const sf::Time & time);
  private:
    SceneNode * mParentNode;
    std::vector<SceneNode*> mChildren; // consider change it to the unique_ptr
  private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final; // implementing sf::Drawable pure virtual function
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    SceneNode & operator=(const SceneNode &);
    //SceneNode(const SceneNode &); // resolve this problem
};

#endif //SCENENODE_H
