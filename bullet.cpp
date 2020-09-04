#include "bullet.h"
#include "assetmanager.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

Bullet::Bullet()
 : mSprite(AssetManager::getTexture(mBulletModel.texturePath()))
{

}

Bullet::Bullet(double angle)
  : Bullet()
{
  setRotation(angle);
  setupBullet();
}

void Bullet::setupBullet()
{
  mSprite.setScale(mBulletModel.width() / static_cast<double>(mSprite.getTextureRect().width),
                   mBulletModel.height() / static_cast<double>(mSprite.getTextureRect().height));
  mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2);
}

void Bullet::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}
