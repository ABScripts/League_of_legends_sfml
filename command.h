#ifndef COMMAND_H
#define COMMAND_H

class ControlableEntity;

class Command
{
public:
  Command() = default;
  virtual ~Command() = default;
  virtual void execute(ControlableEntity *ent) = 0;
};

#endif // COMMAND_H
