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
  sf::Vertex mTrackTowerAngle;
public:
  Tank(TankModel::Type type  = TankModel::Type::Self);
  virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
  void turnLeft(const sf::Time &time) override;
  void turnRight(const sf::Time &time) override;
  void turnUp(const sf::Time &time) override;
  void turnDown(const sf::Time &time) override;
  void mouseMoved(const sf::Vertex &mousePosition);
  void mousePressed(const sf::Vertex &mousePosition) override;
};

#endif // TANK_H
