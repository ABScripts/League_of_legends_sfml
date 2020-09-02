#include "commandsimplementation.h"
#include "tank.h"

void TurnRight::execute(ControlableEntity *ent) {
  ent->turnRight();
}

void TurnLeft::execute(ControlableEntity *ent) {
  ent->turnLeft();
}

void TurnUp::execute(ControlableEntity *ent) {
  ent->turnUp();
}

void TurnDown::execute(ControlableEntity *ent) {
  ent->turnDown();
}

//void MouseMoved::execute(ControlableEntity *ent, const std::pair<double, double> & mousePosition) {
//  ent->mouseMoved(mousePosition);
//}
