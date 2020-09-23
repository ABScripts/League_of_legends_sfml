#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <vector>
#include <map>

class Tank;
class Entity;
class SceneNode;

class GameModel
{
public:
  enum class Layers {
    MapLayer = 0,
    BattlefieldLayer
  };

  GameModel();
  ~GameModel();
  const std::map<Layers, Entity *> &getLayers() const;
  Tank *getPlayer() const;
  const std::vector<SceneNode *> &getEnemies() const;

private:
  // game layers -> defines their childrens` render level
  std::map<Layers, Entity*> mLayers;
  Tank * mPlayer;
  std::vector<SceneNode *> mEnemies;
//  std::vector<std::pair<SceneNode &, SceneNode&> > mCollisionPairs;
};

#endif // GAMEMODEL_H
