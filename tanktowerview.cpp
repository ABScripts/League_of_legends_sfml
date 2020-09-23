#include "tanktowerview.h"
#include "tanktowermodel.h"
#include "assetmanager.h"
#include "bullet.h"
#include <math.h>
#include "SFML/Graphics/RenderTarget.hpp"
#include  <iostream>
#include "SFML/Graphics/RenderStates.hpp"

TankTowerView::TankTowerView(const std::string &towerTexturePath, int shift, Entity *parent)
  : Entity(parent),
    m_TowerModel(new TankTowerModel()),
    mRechargeTime(sf::Time::Zero),
    mGunIsReady(true)
{
  setupTower(towerTexturePath, shift);
}

void TankTowerView::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}

Bullet *TankTowerView::shootBullet(const sf::Time &time, const sf::Vertex &spawnPosition, int rotation)
{
  if (mGunIsReady) {
      mGunIsReady = false;
      mRechargeTime = sf::seconds(m_TowerModel->rechargeTime());
      Bullet * bullet = new Bullet(rotation);
      bullet->setPosition(spawnPosition.position.x, spawnPosition.position.y);
      return bullet;
    }
  return nullptr;
}


void TankTowerView::updateCurrent(const sf::Time &time)
{
  if (!mGunIsReady) {
      mRechargeTime -= time;
      if (mRechargeTime <= sf::Time(sf::seconds(0))) {
          mGunIsReady = true;
        }
    }
}

void TankTowerView::setupTower(const std::string &towerTexturePath, int shift)
{
  adjustTexture(towerTexturePath, m_TowerModel->Width(), m_TowerModel->Height(), 0, shift);
}
