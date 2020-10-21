#ifndef TANKMODEL_H
#define TANKMODEL_H

#include <string>

class TankModel
{ 
public:
  using TexturePaths = std::pair<std::string, std::string>;

  enum class TankType {
    Self = 0,
    Teammate,
    Enemy
  };

  enum class Description {
    Width = 100,
    Height = 100,
    MoveSpeed = 250,
    RotationSpeed = 90,
    Health = 500,
    TimeToNextTankRotation = 500 // in miliseconds
  };

public:
  TankModel() = default;
  TankModel(TankType bodyType, TankType towerType); // resolve this inconvenience as it is not too handy defining private section beforehand.
  short Height() const;
  short Width() const;
  unsigned char MoveSpeed() const;
  unsigned char RotationSpeed() const;
  std::string towerTexturePath() const;
  std::string bodyTexturePath() const;
  int timeToNextTankRotation() const;

  void setHealth(int health);
  int health() const;

private:
  static const TexturePaths mSelfTexturePath;
  static const TexturePaths mEnemyTexturePath;
  static const TexturePaths mTeammateTexturePath;

  int mHealth;
  short int mWidth;
  short int mHeight;
  unsigned char mRotationSpeed;
  unsigned char mMoveSpeed;
  int mTimeToNextTankRotation;
  std::string mBodyTexturePath;
  std::string mTowerTexturePath;
  TankType mBodyType;
  TankType mTowerType;
private:
  void setupTankModel();
  TexturePaths switchTextureSets(const TankType & type);

  friend class Tank;
};

#endif // TANKMODEL_H
