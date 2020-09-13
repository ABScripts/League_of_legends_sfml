#include <iostream>
#include "tank.h"
#include "tankmodel.h"
#include "tanktowerview.h"
#include "assetmanager.h"
#include "mathcore.h"
#include "bullet.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

Tank::Tank(Entity *parent, TankModel::TankType bodyType, TankModel::TankType towerType)
  : ControlableEntity::ControlableEntity(parent),
    mTankModel(new TankModel(bodyType, towerType)),
    mTowerView(new TankTowerView(mTankModel->towerTexturePath(), mTankModel->Height() / 2, this)),
    mSprite(AssetManager::getTexture(mTankModel->bodyTexturePath()))
{
  setupTank();
}

void Tank::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}

void Tank::setupTank() {
  Entity::adjustTexture(mSprite, mTankModel->Width(), mTankModel->Height());
}

// Returns tower`s rotation relatively to the global layer, not to the tank`s body
int Tank::getGlobalRotation() const {
    return getRotation() + mTowerView->getRotation();
}

void Tank::turnLeft(const sf::Time &time) {
  mouseMoved(time, mTrackTowerAngle);
  setRotation(getRotation() - mTankModel->RotationSpeed() * time.asSeconds());
}

void Tank::turnRight(const sf::Time &time) {
  mouseMoved(time, mTrackTowerAngle);
  setRotation(getRotation() + mTankModel->RotationSpeed() * time.asSeconds());
}

void Tank::turnUp(const sf::Time &time) {
  mouseMoved(time, mTrackTowerAngle);
  const auto shift = MathCore::getLineMoveCoefficients(getRotation(), mTankModel->MoveSpeed() * time.asSeconds()); // consider changing these lines to more readable ones
  setPosition(getPosition().x + shift.first, getPosition().y - shift.second);
}

void Tank::turnDown(const sf::Time &time) {
    mouseMoved(time, mTrackTowerAngle);
  const auto shift = MathCore::getLineMoveCoefficients(getRotation(), mTankModel->MoveSpeed() * time.asSeconds());
  setPosition(getPosition().x - shift.first, getPosition().y + shift.second);
}

void Tank::mouseMoved(const sf::Time &time, const sf::Vertex &mousePosition)
{
  mTrackTowerAngle = mousePosition;

  double angle = atan2(mTrackTowerAngle.position.y - getPosition().y,
                       mTrackTowerAngle.position.x - getPosition().x);

  mTowerView->setRotation(MathCore::radToDeg(angle) - getRotation() + 90);
  // + 90 becouse this func means:
   //      90
   //   180 + 0
   //      270
  // At the same time in our coordinate system 90 is replaced with 0 and all left numbers go all the way down.
}

void Tank::mousePressed(const sf::Time &time, const sf::Vertex &mousePosition)
{
     sf::Vertex spawnPoint = MathCore::pointOnCircle(this,
                                                     mTankModel->Height(),
                                                     getGlobalRotation() - 90);
     if (Bullet * bullet = mTowerView->shootBullet(time,
                                                   sf::Vector2f(spawnPoint.position.x + getPosition().x, spawnPoint.position.y + getPosition().y),
                                                   getGlobalRotation()) )
        {
        attachToParent(bullet);
        }
}

