#include "commandsimplementation.h"
#include "tank.h"

void TurnRight::execute(ControlableEntity *entity, const sf::Time &t) {
  entity->turnRight(t);
}

void TurnLeft::execute(ControlableEntity *entity, const sf::Time &t) {
  entity->turnLeft(t);
}

void TurnUp::execute(ControlableEntity *entity, const sf::Time &t) {
  entity->turnUp(t);
}

void TurnDown::execute(ControlableEntity *entity, const sf::Time &t) {
  entity->turnDown(t);
}

//void MouseMoved::execute(ControlableEntity *ent, const std::pair<double, double> & mousePosition) {
//  ent->mouseMoved(mousePosition);
//}
