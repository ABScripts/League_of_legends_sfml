#ifndef ENTITY_H
#define ENTITY_H

#include "scenenode.h"

namespace sf {
  class Sprite;
}

class Entity : public SceneNode
{
public:
  Entity(Entity * parent = nullptr);
protected:
  void adjustTexture(sf::Sprite &sprite, const int & actualWidth, const int & actualHeight, const int & shiftX = 0, const int & shiftY = 0);
};

#endif // ENTITY_H
