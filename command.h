#ifndef COMMAND_H
#define COMMAND_H

class Tank;

class Command
{
public:
  Command() = default;
  virtual ~Command() = default;
  virtual void execute(Tank &tank) = 0;
};

#endif // COMMAND_H
