#ifndef BULLET_H
#define BULLET_H

#include "entity_system/entity.h"
#include "SFML/Graphics/Sprite.hpp"
#include "bulletmodel.h"

class Bullet : public Entity
{
public:
  Bullet();
  Bullet(double angle, sf::Vector2f spawnPoint);
  void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
  void updateCurrent(const sf::Time &time) override;
  int getDamage() const;
  void destroy();

  float width() const;
  float height() const;

private:
  BulletModel mBulletModel;
private:
  void setupBullet(sf::Vector2f spawnPoint);
};

#endif // BULLET_H
