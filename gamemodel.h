#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <vector>
#include "test_entity_system/entity.h"

class Tank;

class GameModel
{
public:
  GameModel();
  const std::vector<Entity*> & getTanks() const;
private:
  std::vector<Entity*> m_tanks;
};

#endif // GAMEMODEL_H
