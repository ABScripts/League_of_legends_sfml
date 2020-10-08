#ifndef CONTROLABLEENTITY_H
#define CONTROLABLEENTITY_H

#include "entity.h"
#include <memory>
#include <list>
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Command;

class ControlableEntity : public Entity
{
public:
  ControlableEntity(Entity * parent = nullptr);
  virtual void turnLeft(const sf::Time &time) = 0;
  virtual void turnRight(const sf::Time &time) = 0;
  virtual void turnUp(const sf::Time &time) = 0;
  virtual void turnDown(const sf::Time &time) = 0;
  virtual void mouseMoved(const sf::Time &time, const sf::Vertex &mousePosition) = 0;
  virtual void mousePressed(const sf::Time &time, const sf::Vertex &mousePosition) = 0;
  virtual void update(const sf::Time & time,  std::shared_ptr<std::list<Command*> > mCommands);
};

#endif // CONTROLABLEENTITY_H
