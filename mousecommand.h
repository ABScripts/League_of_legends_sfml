#ifndef MOUSECOMMAND_H
#define MOUSECOMMAND_H

#include "command.h"
#include "SFML/Graphics/Vertex.hpp"

class MouseCommand : public Command
{
public:
  void execute(ControlableEntity *, const sf::Time&) override;
  void setMousePosition(const sf::Vertex &newPos) {
    mMousePosition = newPos;
  }

protected:
  sf::Vertex mMousePosition;
};

#endif // MOUSECOMMAND_H
