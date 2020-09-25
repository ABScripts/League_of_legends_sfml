#ifndef ENTITY_H
#define ENTITY_H

#include "scenenode.h"
#include "SFML/Graphics/Sprite.hpp"

class Entity : public SceneNode
{
public:
  Entity(Entity * parent = nullptr);
protected:
  void adjustTexture(const std::string &texturePath, const int & actualWidth, const int & actualHeight, const int & shiftX = 0, const int & shiftY = 0);
  sf::FloatRect getBoundingRect() const;

protected:
  sf::Sprite mSprite;
  bool mIsDestroyed;

private:
  static const std::string mDefaultTexturePath;
};

#endif // ENTITY_H
