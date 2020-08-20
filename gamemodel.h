#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <vector>

class Tank;

class GameModel
{
public:
  GameModel();
  std::vector<Tank> & getTanks();
private:
  std::vector<Tank> m_tanks;
};

#endif // GAMEMODEL_H
