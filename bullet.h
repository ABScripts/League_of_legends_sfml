#ifndef BULLET_H
#define BULLET_H

#include "test_entity_system/entity.h"
#include "SFML/Graphics/Sprite.hpp"
#include "bulletmodel.h"

class Bullet : public Entity
{
public:
  Bullet();
  Bullet(double angle);

  void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
  BulletModel mBulletModel;
  sf::Sprite mSprite;
private:
  void setupBullet();
};

#endif // BULLET_H
