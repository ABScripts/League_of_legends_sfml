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

Tank::Tank(Entity *parent, TankModel::TankType bodyType, TankModel::TankType towerType, float x, float y)
  : ControlableEntity::ControlableEntity(parent)
  , mTankModel(new TankModel(bodyType, towerType))
  , mTowerView(new TankTowerView(mTankModel->towerTexturePath(), mTankModel->Height() / 2, this))
  , mRotationIsAllowed(true)
  , mId_tempVar(++mNumberOfTanks_tempVar)
  , mVelocityVector(0, 0)
  , mTrackTowerAngle(0, 0)
{

  setupTank(x, y);
}

void Tank::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}

void Tank::setupTank(float x, float y) {
  Entity::adjustTexture(mTankModel->bodyTexturePath(), mTankModel->Width(), mTankModel->Height());
  setPosition(x, y);
  mCenter = {getBoundingRect().left + mTankModel->Width() / 2, getBoundingRect().top + mTankModel->Height() / 2};
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
  mouseMoved(time, mTrackTowerAngle);
  setRotation(getRotation() - mTankModel->RotationSpeed() * time.asSeconds());
}

void Tank::turnRight(const sf::Time &time) {
  mouseMoved(time, mTrackTowerAngle);
  setRotation(getRotation() + mTankModel->RotationSpeed() * time.asSeconds());
}

void Tank::turnUp(const sf::Time &time) {
  mouseMoved(time, mTrackTowerAngle);
  sf::Vector2f shift = MathCore::getLineMoveCoefficients(getRotation(), mTankModel->MoveSpeed() * time.asSeconds()); // consider changing these lines to more readable ones
  mVelocityVector = {shift.x, -shift.y};
  setPosition(getPosition().x + mVelocityVector.x, getPosition().y + mVelocityVector.y);
  mCenter +=  mVelocityVector;
}

void Tank::turnDown(const sf::Time &time) {
  mouseMoved(time, mTrackTowerAngle);
  sf::Vector2f shift = MathCore::getLineMoveCoefficients(getRotation(), mTankModel->MoveSpeed() * time.asSeconds());
  mVelocityVector = {-shift.x, shift.y};
  setPosition(getPosition().x + mVelocityVector.x, getPosition().y + mVelocityVector.y);
  mCenter +=  mVelocityVector;
}

void Tank::mouseMoved(const sf::Time &time, const sf::Vector2f &mousePosition)
{
  mTrackTowerAngle = mousePosition;

  double angle = atan2(mTrackTowerAngle.y - getPosition().y,
                       mTrackTowerAngle.x - getPosition().x);

  mTowerView->setRotation(MathCore::radToDeg(angle) - getRotation() + 90);
}

float Tank::width() const
{
  return mTankModel->Width();
}

float Tank::height() const
{
  return mTankModel->Height();
}

void Tank::mousePressed(const sf::Time &time, const sf::Vector2f &mousePosition)
{


  sf::Vector2f spawnPoint = MathCore::pointOnCircle(this,
                                                    mTankModel->Height() + 4,
                                                    getGlobalRotation() - 90);

  if (Bullet * bullet = mTowerView->shootBullet(time,
  {spawnPoint.x + getPosition().x, spawnPoint.y + getPosition().y},
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
      std::cout << "[TEST LOG] - Bullet collided with tank.\n";
      damage(bullet->getDamage());
      bullet->destroy();
    }
  else if (Tank *tank = dynamic_cast<Tank*>(collidedObj)) {
      setPosition(getPosition().x - mVelocityVector.x, getPosition().y - mVelocityVector.y);
      mCenter -= mVelocityVector;
    }

  if (!isAlive()) {
      std::cout << "[TEST LOG] - Tank with id " << mId_tempVar << " have been destroyed.\n"; // test code
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
