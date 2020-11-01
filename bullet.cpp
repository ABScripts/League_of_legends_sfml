#include "bullet.h"
#include <iostream>
#include "assetmanager.h"
#include "mathcore.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

Bullet::Bullet()
{

}

Bullet::Bullet(double angle, sf::Vector2f spawnPoint)
  : Bullet()
{
  setRotation(angle);
  setupBullet(spawnPoint);
}

void Bullet::setupBullet(sf::Vector2f spawnPoint)
{
  setPosition(spawnPoint.x, spawnPoint.y);
  Entity::adjustTexture(mBulletModel.texturePath(), mBulletModel.width(), mBulletModel.height());
  mCenter = {getBoundingRect().left + mBulletModel.width() / 2, getBoundingRect().top + mBulletModel.height() / 2};
}

void Bullet::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}

void Bullet::updateCurrent(const sf::Time &time)
{
  sf::Vector2f newSpot = MathCore::getLineMoveCoefficients(getRotation(), mBulletModel.speed() * time.asSeconds());
  setPosition(getPosition().x + newSpot.x, getPosition().y - newSpot.y);
  mCenter += {newSpot.x, -newSpot.y};
}

int Bullet::getDamage() const
{
  return mBulletModel.damage();
}

void Bullet::destroy()
{
  mIsDestroyed = true;
}

float Bullet::width() const
{
 return mBulletModel.width();
}

float Bullet::height() const
{
  return mBulletModel.height();
}
