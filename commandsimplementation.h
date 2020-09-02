#ifndef COMMANDSIMPLEMENTATION_H
#define COMMANDSIMPLEMENTATION_H

class Entity;
#include "command.h"
#include <utility>

class TurnLeft : public Command
{
public:
  virtual void execute(ControlableEntity *ent) override;
};

class TurnRight : public Command
{
public:
  virtual void execute(ControlableEntity *ent) override;
};

class TurnUp: public Command
{
public:
  virtual void execute(ControlableEntity *ent) override;
};

class TurnDown : public Command
{
public:
  virtual void execute(ControlableEntity *ent) override;
};

//class MouseMoved : public Command
//{
//public:
//  virtual void execute(ControlableEntity *ent, const std::pair<double, double> & mousePosition) override;
//};

#endif // COMMANDSIMPLEMENTATION_H
