#include "gamemodel.h"
#include "tank.h"

GameModel::GameModel() {
  m_tanks.push_back(new Tank()); // adding one tank
}

const std::vector<Entity*> &GameModel::getTanks() const {  // should be changed to const func returning const ref
  return m_tanks;
}
