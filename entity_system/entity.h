#ifndef ENTITY_H
#define ENTITY_H

#include "scenenode.h"
#include "SFML/Graphics/Sprite.hpp"

class Entity : public SceneNode
{
public:
  Entity(Entity * parent = nullptr);
  void setDestroyedStatus(bool isDestroyed);

  const sf::Sprite *getSprite() const;
  sf::FloatRect getBoundingRect() const;

  float width() const override {};
  float height() const override {};
  sf::Vector2f center() const override { return mCenter; }

protected:
  void adjustTexture(const std::string &texturePath, const int & actualWidth, const int & actualHeight, const int & shiftX = 0, const int & shiftY = 0);

protected:
  sf::Sprite mSprite;
  sf::Vector2f mCenter;

private:
  static const std::string mDefaultTexturePath;

  friend class QuadTree;
};

#endif // ENTITY_H
