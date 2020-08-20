#ifndef TANK_H
#define TANK_H

#include <vector>

#include "SFML/Graphics/Sprite.hpp"
#include "tankmodel.h" // consider changing this part

class TankModel;
class TankTowerView;

class Tank : public sf::Sprite
{
private:
  TankModel * m_TankModel; // should be replaced in future with unique ptr
  TankTowerView * m_TowerView;
private:
  void setupTank();
public:
  std::vector<const sf::Sprite*> m_drawableObjects;
public:
  Tank(TankModel::Type type  = TankModel::Type::Self);
  void turnLeft();
  void turnRight();
  void turnUp();
  void turnDown();
  const std::vector<const sf::Sprite *> &drawableObjects() const;
};

#endif // TANK_H
