#ifndef TANK_H
#define TANK_H

#include "SFML/Graphics/Sprite.hpp"
#include "entity_system/controlableentity.h"
#include "tankmodel.h" // consider changing this part

class TankTowerView;

class Tank : public ControlableEntity
{
  static int mNumberOfTanks_tempVar;
private:
  TankModel * mTankModel; // should be replaced in future with unique ptr
  TankTowerView * mTowerView;
  sf::Vertex mTrackTowerAngle;
  int mId_tempVar;
private:
  void setupTank();
  int getGlobalRotation() const;
public:
  Tank(Entity * parent = nullptr, TankModel::TankType bodyType  = TankModel::TankType::Self, TankModel::TankType towerType = TankModel::TankType::Self,
       double xposition = 0, double yposition = 0);
  virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
  void turnLeft(const sf::Time &time) override;
  void turnRight(const sf::Time &time) override;
  void turnUp(const sf::Time &time) override;
  void turnDown(const sf::Time &time) override;
  void mouseMoved(const sf::Time &time, const sf::Vertex &mousePosition) override;
  void mousePressed(const sf::Time &time, const sf::Vertex &mousePosition) override;
  void applyCollisionRules() override;

  bool isDestroyed() const {return mIsDestroyed;};
};

#endif // TANK_H
