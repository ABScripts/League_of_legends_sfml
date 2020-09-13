#include "bullet.h"
#include <iostream>
#include "assetmanager.h"
#include "mathcore.h"
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
  Entity::adjustTexture(mSprite, mBulletModel.width(), mBulletModel.height());
}

void Bullet::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}

void Bullet::updateCurrent(const sf::Time &time)
{
  std::pair<double, double> newSpot = MathCore::getLineMoveCoefficients(getRotation(), mBulletModel.speed() * time.asSeconds());
  setPosition(getPosition().x + newSpot.first, getPosition().y - newSpot.second);
}
