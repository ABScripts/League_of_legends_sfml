#ifndef COMMANDSIMPLEMENTATION_H
#define COMMANDSIMPLEMENTATION_H

class Entity;

#include "command.h"
#include "mousecommand.h"
#include "SFML/Graphics/Vertex.hpp"

class TurnLeft : public Command
{
public:
  virtual void execute(ControlableEntity *, const sf::Time &) override;
};

class TurnRight : public Command
{
public:
  virtual void execute(ControlableEntity *, const sf::Time &) override;
};

class TurnUp: public Command
{
public:
  virtual void execute(ControlableEntity *, const sf::Time &) override;
};

class TurnDown : public Command
{
public:
  virtual void execute(ControlableEntity *, const sf::Time &) override;
};

class MousePressed : public MouseCommand
{
public:
  void execute(ControlableEntity *, const sf::Time &) override;
};


#endif // COMMANDSIMPLEMENTATION_H
