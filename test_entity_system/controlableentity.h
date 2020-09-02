#ifndef CONTROLABLEENTITY_H
#define CONTROLABLEENTITY_H

#include "entity.h"

class ControlableEntity : public Entity
{
public:
  ControlableEntity() = default;

  virtual void turnLeft() = 0;
  virtual void turnRight() = 0;
  virtual void turnUp() = 0;
  virtual void turnDown() = 0;
  virtual void mouseMoved(const std::pair<double, double> &) = 0;
};

#endif // CONTROLABLEENTITY_H
