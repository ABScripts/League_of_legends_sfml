#ifndef TANKTOWERVIEW_H
#define TANKTOWERVIEW_H

#include <string>
#include "SFML/Graphics/Sprite.hpp"
#include "entity_system/entity.h"

class Bullet;
class TankTowerModel;
enum class TankType;

class TankTowerView : public Entity
{
public:
  TankTowerView() = default;
  TankTowerView(const std::string & towerTexturePath, int shift, Entity * parent = nullptr);
  virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
  Bullet *shootBullet(const sf::Time & time, const sf::Vertex &spawnPositio, int rotation);
  void updateCurrent(const sf::Time & time);
private:
  TankTowerModel * m_TowerModel;
  sf::Time mRechargeTime;
  bool mGunIsReady;
private:
  void setupTower(const std::string &towerTexturePath, int shift);

  friend class Tank;
};

#endif // TANKTOWERVIEW_H
