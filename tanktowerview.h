#ifndef TANKTOWERVIEW_H
#define TANKTOWERVIEW_H

#include <string>
#include "SFML/Graphics/Sprite.hpp"
#include "test_entity_system/entity.h"

class TankTowerModel;

class TankTowerView : public Entity
{
public:
  TankTowerView() = default;
  TankTowerView(const std::string & towerTexturePath, int shift);
  virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
private:
  TankTowerModel * m_TowerModel;
  sf::Sprite mSprite;
private:
  void setupTower(const std::string & towerTexturePath, int shift);
  void turnLeft() {};
  void turnRight()  {};
  void turnUp()  {};
  void turnDown()  {};
};

#endif // TANKTOWERVIEW_H
