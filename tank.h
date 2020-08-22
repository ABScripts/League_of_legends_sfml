#ifndef TANK_H
#define TANK_H

#include <vector>

#include "SFML/Graphics/Sprite.hpp"
#include "test_entity_system/entity.h"
#include "tankmodel.h" // consider changing this part

class TankModel;
class TankTowerView;

class Tank : public Entity
{
private:
  TankModel * m_TankModel; // should be replaced in future with unique ptr
  TankTowerView * m_TowerView;
private:
  void setupTank();
  sf::Sprite mSprite;
public:
  std::vector<const sf::Sprite*> m_drawableObjects;
public:
  Tank(TankModel::Type type  = TankModel::Type::Self);
  virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
  void turnLeft();
  void turnRight();
  void turnUp();
  void turnDown();
};

#endif // TANK_H
