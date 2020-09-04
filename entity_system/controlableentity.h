#ifndef CONTROLABLEENTITY_H
#define CONTROLABLEENTITY_H

#include "entity.h"
#include "SFML/Graphics/Vertex.hpp"

class ControlableEntity : public Entity
{
public:
  ControlableEntity() = default;

  virtual void turnLeft(const sf::Time &time) = 0;
  virtual void turnRight(const sf::Time &time) = 0;
  virtual void turnUp(const sf::Time &time) = 0;
  virtual void turnDown(const sf::Time &time) = 0;
  virtual void mouseMoved(const sf::Vertex &mousePosition) = 0;
  virtual void mousePressed(const sf::Vertex &mousePosition) = 0;
};

#endif // CONTROLABLEENTITY_H
