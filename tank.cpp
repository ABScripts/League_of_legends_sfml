#include <iostream>
#include "tank.h"
#include "tankmodel.h"
#include "assetmanager.h"
#include "mathcore.h"
#include "tanktowerview.h"
#include "bullet.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

Tank::Tank(TankModel::Type type)
  : m_TankModel(new TankModel(type)),
    m_TowerView(new TankTowerView(m_TankModel->TowerTexturePath(), m_TankModel->Height() / 2)),
    mSprite(AssetManager::getTexture(m_TankModel->TexturePath()))
{
  attachChild(m_TowerView);
  setupTank();
}

void Tank::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}

void Tank::setupTank() {
 // mSprite.setTexture(AssetManager::getTexture(m_TankModel->TexturePath())); // actually setting texture
  mSprite.setScale(m_TankModel->Width() / static_cast<double>(mSprite.getTextureRect().width),
                   m_TankModel->Height() / static_cast<double>(mSprite.getTextureRect().height));
  mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2);
}

void Tank::turnLeft(const sf::Time &time) {
  mouseMoved(mTrackTowerAngle);
  setRotation(getRotation() - m_TankModel->RotationSpeed() * time.asSeconds());
}

void Tank::turnRight(const sf::Time &time) {
  mouseMoved(mTrackTowerAngle);
  setRotation(getRotation() + m_TankModel->RotationSpeed() * time.asSeconds());
}

void Tank::turnUp(const sf::Time &time) {
    mouseMoved(mTrackTowerAngle);
  const auto shift = MathCore::getLineMoveCoefficients(getRotation(), m_TankModel->m_MoveSpeed * time.asSeconds()); // consider changing these lines to more readable ones
  setPosition(getPosition().x + shift.first, getPosition().y - shift.second);
}

void Tank::turnDown(const sf::Time &time) {
    mouseMoved(mTrackTowerAngle);
  const auto shift = MathCore::getLineMoveCoefficients(getRotation(), m_TankModel->m_MoveSpeed * time.asSeconds());
  setPosition(getPosition().x - shift.first, getPosition().y + shift.second);
}

void Tank::mouseMoved(const sf::Vertex &mousePosition)
{
  mTrackTowerAngle = mousePosition;

  double angle = atan2(mTrackTowerAngle.position.y - getPosition().y,
                       mTrackTowerAngle.position.x - getPosition().x);

  m_TowerView->setRotation(MathCore::radToDeg(angle) - getRotation() + 90);
  // + 90 becouse this func means:
   //      90
   //   180 + 0
   //      270
  // At the same time in our coordinate system 90 is replaced with 0 and all left numbers go all the way down.
}

void Tank::mousePressed(const sf::Vertex &mousePosition)
{
     sf::Vertex spawnPoint = MathCore::pointOnCircle(this,
                                                     m_TankModel->Height(),
                                                     m_TowerView->getRotation() - 90);

     Bullet * bullet = new Bullet(m_TowerView->getRotation());
     bullet->setPosition(spawnPoint.position.x, spawnPoint.position.y);
     attachChild(bullet);
}

