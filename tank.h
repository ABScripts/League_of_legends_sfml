#ifndef TANK_H
#define TANK_H

#include "SFML/Graphics/Sprite.hpp"
#include "entity_system/controlableentity.h"
#include "tankmodel.h" // consider changing this part
#include "SFML/System/Vector2.hpp"

class TankTowerView;

class Tank : public ControlableEntity
{
  static int mNumberOfTanks_tempVar; // temp var
private:
  TankModel * mTankModel; // should be replaced in future with unique ptr
  TankTowerView * mTowerView;
  sf::Vector2<double> mVelocityVector;
  bool mRotationIsAllowed;
  sf::Time mTimeToNextRotation;
  std::shared_ptr<std::list<Command*> > mCommands;
  int mId_tempVar; // test variable
  sf::Vector2f mCenterPoint;

private:
  void setupTank(float x, float y);
  int getGlobalRotation() const;
  bool isAlive() const;
  void applyRotation(int rotationSpeed);

public:
  Tank(Entity * parent = nullptr, TankModel::TankType bodyType  = TankModel::TankType::Self, TankModel::TankType towerType = TankModel::TankType::Self,
       double xposition = 0, double yposition = 0);
  virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
  virtual void updateCurrent(const sf::Time & time) override;
  virtual void applyCollisionToSelf(SceneNode *collidedObj = nullptr) override;
  void damage(int damage);

  void turnLeft(const sf::Time &time) override;
  void turnRight(const sf::Time &time) override;
  void turnUp(const sf::Time &time) override;
  void turnDown(const sf::Time &time) override;
  void mousePressed(const sf::Time &time, const sf::Vertex &mousePosition) override;

  void setCommands(const std::shared_ptr<std::list<Command *> > &commands);
  std::shared_ptr<std::list<Command *> > getCommands() const;

  friend class TankTowerView;
  sf::Vector2f getCenterPoint() const;
};

#endif // TANK_H
