#ifndef TANKTOWERVIEW_H
#define TANKTOWERVIEW_H

#include <string>
#include "SFML/Graphics/Sprite.hpp"

class TankTowerModel;

class TankTowerView : public sf::Sprite
{
public:
  TankTowerView() = default;
  TankTowerView(const std::string & towerTexturePath);
private:
  TankTowerModel * m_TowerModel;
private:
  void setupTower(const std::string & towerTexturePath);
};

#endif // TANKTOWERVIEW_H
