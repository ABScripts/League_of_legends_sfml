#include "entity.h"
#include "SFML/Graphics/Sprite.hpp"

/* Actually this functin uses the actual size of the entity (not the origin texture`s size) and apply
 * that size to the texture`s. In this way we obtain the entity of the exact size we wanted to.*/
Entity::Entity(Entity *parent)
{
  if (parent)
    parent->attachChild(this);
}

void Entity::adjustTexture(sf::Sprite &sprite, const int & actualWidth, const int & actualHeight, const int & shiftX, const int & shiftY)
{
  sprite.setScale(actualWidth / static_cast<double>(sprite.getTextureRect().width),
                   actualHeight / static_cast<double>(sprite.getTextureRect().height));
  sprite.setOrigin(sprite.getTextureRect().width / 2 + shiftX, sprite.getTextureRect().height / 2 + shiftY);
}
