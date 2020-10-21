#include "tank.h"
#include "tankmodel.h"
#include "tanktowerview.h"
#include "assetmanager.h"
#include "mathcore.h"
#include "bullet.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "gameobjecteventpull.h"

int Tank::mNumberOfTanks_tempVar = 0;

Tank::Tank(Entity *parent, TankModel::TankType bodyType, TankModel::TankType towerType, double xposition, double yposition)
  : ControlableEntity::ControlableEntity(parent)
  , mTankModel(new TankModel(bodyType, towerType))
  , mTowerView(new TankTowerView(mTankModel->towerTexturePath(), mTankModel->Height() / 2, this))
  , mId_tempVar(++mNumberOfTanks_tempVar)
  , mVelocityVector(0, 0)
  , mRotationIsAllowed(true)
  , mCenterPoint(getPosition().x + getBoundingRect().width / 2, getPosition().y + getBoundingRect().height / 2)
{
  setupTank(xposition, yposition);
}

void Tank::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}

sf::Vector2f Tank::getCenterPoint() const
{
  return mCenterPoint;
}

void Tank::setupTank(float x, float y) {
  setPosition(x, y);
  Entity::adjustTexture(mTankModel->bodyTexturePath(), mTankModel->Width(), mTankModel->Height());
}

// Returns tower`s rotation relatively to the global layer, not to the tank`s body
int Tank::getGlobalRotation() const {
  return getRotation() + mTowerView->getRotation();
}

bool Tank::isAlive() const
{
  return mTankModel->health() > 0;
}

void Tank::applyRotation(int rotationSpeed)
{
  if (mRotationIsAllowed) {
      mRotationIsAllowed = false;
      mTimeToNextRotation = sf::milliseconds(mTankModel->timeToNextTankRotation());
      setRotation(getRotation() + rotationSpeed);
    }
}

void Tank::turnLeft(const sf::Time &time) {
//  static_cast<void>(time);
//  applyRotation(-mTankModel->RotationSpeed());
  setRotation(getRotation() - 120 * time.asSeconds());
  qDebug() << "Turn right: "<< getRotation() << "\n";
}

void Tank::turnRight(const sf::Time &time) {
//  static_cast<void>(time);
//  applyRotation(mTankModel->RotationSpeed());
   setRotation(getRotation() + 120 * time.asSeconds());
  qDebug() << "Turn right: "<< getRotation() << "\n";
}

void Tank::turnUp(const sf::Time &time) {
  const auto shift = MathCore::getLineMoveCoefficients(getRotation(), mTankModel->MoveSpeed() * time.asSeconds()); // consider changing these lines to more readable ones
  mVelocityVector = {shift.first, -shift.second};
  setPosition(getPosition().x + mVelocityVector.x, getPosition().y + mVelocityVector.y);
  mCenterPoint.x +=  mVelocityVector.x; // put in ...
  mCenterPoint.y +=  mVelocityVector.y;
}

void Tank::turnDown(const sf::Time &time) {
  const auto shift = MathCore::getLineMoveCoefficients(getRotation(), mTankModel->MoveSpeed() * time.asSeconds());
  mVelocityVector = {-shift.first, shift.second};
  setPosition(getPosition().x + mVelocityVector.x, getPosition().y + mVelocityVector.y);
  mCenterPoint.x +=  mVelocityVector.x;
  mCenterPoint.y +=  mVelocityVector.y;
}

void Tank::mousePressed(const sf::Time &time, const sf::Vertex &mousePosition)
{
     static_cast<void>(mousePosition);
     sf::Vertex spawnPoint = MathCore::pointOnCircle(this,
                                                     mTankModel->Height() + 4,
                                                     getGlobalRotation() - 90);

     if (Bullet * bullet = mTowerView->shootBullet(time,
                                                   sf::Vector2f(spawnPoint.position.x + getPosition().x, spawnPoint.position.y + getPosition().y),
                                                   getGlobalRotation()) )
        {
          attachToParent(bullet);
          GameObjectEventPull::pushEvent(bullet, GameObjectEventPull::EventTypes::RegisterInQuadTree);
        }
}

void Tank::applyCollisionToSelf(SceneNode *collidedObj)
{
  if (!collidedObj) return;

  if (Bullet *bullet = dynamic_cast<Bullet*>(collidedObj)){
      damage(bullet->getDamage());
      bullet->destroy();
    }
  else if (Tank *tank = dynamic_cast<Tank*>(collidedObj)) {
      setPosition(getPosition().x - mVelocityVector.x, getPosition().y - mVelocityVector.y);
    }

  if (!isAlive()) {
      std::cout << "Tank with id " << mId_tempVar << " have been destroyed!\n"; // test code
      mIsDestroyed = true;
      mTowerView->setDestroyedStatus(true);
    }
}

void Tank::damage(int damage)
{
  mTankModel->setHealth(mTankModel->health() - damage);
}

void Tank::updateCurrent(const sf::Time &time)
{
  if (!mRotationIsAllowed) {
      mTimeToNextRotation -= time;
      if (mTimeToNextRotation <= sf::Time(sf::seconds(0))) {
          mRotationIsAllowed = true;
        }
    }
}

void Tank::setCommands(const std::shared_ptr<std::list<Command *> > &commands)
{
  mCommands = commands;
}

std::shared_ptr<std::list<Command *> > Tank::getCommands() const
{
  return mCommands;
}
