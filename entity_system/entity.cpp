#include "entity.h"
#include "assetmanager.h"
#include "SFML/Graphics/Sprite.hpp"

const std::string Entity::mDefaultTexturePath = "res/default.png";

/* Actually this functin uses the actual size of the entity (not the origin texture`s size) and apply
 * that size to the texture`s. In this way we obtain the entity of the exact size we wanted to.*/
Entity::Entity(Entity *parent)
  : mSprite(AssetManager::getTexture(mDefaultTexturePath))
{
  if (parent)
    parent->attachChild(this);
}

void Entity::adjustTexture(const std::string & texturePath, const int & actualWidth, const int & actualHeight, const int & shiftX, const int & shiftY)
{
  mSprite.setTexture(AssetManager::getTexture(texturePath), true);
  mSprite.setScale(actualWidth / static_cast<double>(mSprite.getTextureRect().width),
                   actualHeight / static_cast<double>(mSprite.getTextureRect().height));
  mSprite.setOrigin(mSprite.getTextureRect().width / 2.f + shiftX, mSprite.getTextureRect().height / 2.f + shiftY);
}

sf::FloatRect Entity::getBoundingRect() const
{
  return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

const sf::Sprite* Entity::getSprite() const
{
  return &mSprite;
}

void Entity::setDestroyedStatus(bool isDestroyed)
{
  mIsDestroyed = isDestroyed;
}

