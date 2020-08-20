#include "commandsimplementation.h"
#include "tank.h"

void TurnRight::execute(Tank &tank) {
  tank.turnRight();
}

void TurnLeft::execute(Tank &tank) {
  tank.turnLeft();
}

void TurnUp::execute(Tank &tank) {
  tank.turnUp();
}

void TurnDown::execute(Tank &tank) {
  tank.turnDown();
}
