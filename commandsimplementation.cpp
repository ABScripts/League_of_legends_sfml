#include "commandsimplementation.h"
#include "entity_system/controlableentity.h"

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

void MousePressed::execute(ControlableEntity *entity, const sf::Time &time)
{
  entity->mousePressed(time, mMousePosition);
}
