#include "gamemodel.h"
#include "tank.h"

GameModel::GameModel()
{
  m_tanks.push_back(Tank()); // aading one tank
}

std::vector<Tank> &GameModel::getTanks()  // should be changed to const func returning const ref
{
  return m_tanks;
}
