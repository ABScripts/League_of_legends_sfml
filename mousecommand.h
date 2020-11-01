#ifndef MOUSECOMMAND_H
#define MOUSECOMMAND_H

#include "command.h"
#include "SFML/Graphics/Vertex.hpp"

class MouseCommand : public Command
{
public:
  void execute(ControlableEntity *, const sf::Time&) override;
  void setMousePosition(const sf::Vector2f &newPos) {
    mMousePosition = newPos;
  }

protected:
  sf::Vector2f mMousePosition;
};

#endif // MOUSECOMMAND_H
