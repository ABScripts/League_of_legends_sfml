#ifndef COMMANDSIMPLEMENTATION_H
#define COMMANDSIMPLEMENTATION_H

#include "command.h"

class TurnLeft : public Command
{
public:
  virtual void execute(Tank &tank) override;
};

class TurnRight : public Command
{
public:
  virtual void execute(Tank &tank) override;
};

class TurnUp: public Command
{
public:
  virtual void execute(Tank &tank) override;
};

class TurnDown : public Command
{
public:
  virtual void execute(Tank &tank) override;
};

#endif // COMMANDSIMPLEMENTATION_H
