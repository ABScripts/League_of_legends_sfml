#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <vector>
#include <map>

class Entity;
class Tank;

class GameModel
{
  enum class Layers {
    MapLayer = 0,
    BattlefieldLayer
  };

public:  
  GameModel();
  ~GameModel();
  const std::map<Layers, Entity *> &getLayers() const;
  Tank *getPlayer() const;

private:
  // game layers -> defines their childrens` render level
  std::map<Layers, Entity*> mLayers;
  Tank * mPlayer;
};

#endif // GAMEMODEL_H
