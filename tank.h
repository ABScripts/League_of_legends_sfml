#ifndef TANK_H
#define TANK_H

#include <vector>

#include "SFML/Graphics/Sprite.hpp"
#include "test_entity_system/controlableentity.h"
#include "tankmodel.h" // consider changing this part

class TankModel;
class TankTowerView;

class Tank : public ControlableEntity
{
private:
  TankModel * m_TankModel; // should be replaced in future with unique ptr
  TankTowerView * m_TowerView;
private:
  void setupTank();
  sf::Sprite mSprite;
public:
  Tank(TankModel::Type type  = TankModel::Type::Self);
  virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
  void turnLeft(sf::Time time);
  void turnRight(sf::Time time);
  void turnUp(sf::Time time);
  void turnDown(sf::Time time);
  void mouseMoved(const std::pair<double, double> & mousePosition);
};

#endif // TANK_H
