#ifndef COMMAND_H
#define COMMAND_H

#include "SFML/System/Time.hpp"
class ControlableEntity;

class Command
{
public:
  Command() = default;
  virtual ~Command() = default;
  virtual void execute(ControlableEntity *, const sf::Time&) = 0;
};

#endif // COMMAND_H
