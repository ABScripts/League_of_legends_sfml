#include "commandsimplementation.h"
#include "tank.h"

void TurnRight::execute(ControlableEntity *entity, const sf::Time &time) {
  entity->turnRight(time);
}

void TurnLeft::execute(ControlableEntity *entity, const sf::Time &time) {
  entity->turnLeft(time);
}

void TurnUp::execute(ControlableEntity *entity, const sf::Time &time) {
  entity->turnUp(time);
}

void TurnDown::execute(ControlableEntity *entity, const sf::Time &time) {
  entity->turnDown(time);
}

void MouseMoved::execute(ControlableEntity *entity, const sf::Time &)
{
  entity->mouseMoved(mMousePosition);
}

void MousePressed::execute(ControlableEntity *entity, const sf::Time &)
{
  entity->mousePressed(mMousePosition);
}
