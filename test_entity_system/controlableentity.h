#ifndef CONTROLABLEENTITY_H
#define CONTROLABLEENTITY_H

#include "entity.h"

class ControlableEntity : public Entity
{
public:
  ControlableEntity() = default;

  virtual void turnLeft(sf::Time) = 0;
  virtual void turnRight(sf::Time) = 0;
  virtual void turnUp(sf::Time) = 0;
  virtual void turnDown(sf::Time) = 0;
  virtual void mouseMoved(const std::pair<double, double> &) = 0;
};

#endif // CONTROLABLEENTITY_H
