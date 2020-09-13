#ifndef COMMAND_H
#define COMMAND_H

#include "SFML/System/Time.hpp"
class ControlableEntity;

class Command
{
  enum CommandType {
    buttonEvent, mouseEvent
  };
public:
  virtual void execute(ControlableEntity *, const sf::Time&) = 0;
private:
};

#endif // COMMAND_H
