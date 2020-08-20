#ifndef TANKMODEL_H
#define TANKMODEL_H

#include <string>

class TankModel
{ 
public:
  using TexturePaths = std::pair<std::string, std::string>;

private:
  static const TexturePaths m_selfTexturePath;
  static const TexturePaths m_teammateTexturePath;
  static const TexturePaths m_enemyTexturePath;

  enum class Type {
    Self = 0,
    Teammate,
    Enemy
  };

  enum class Description {
    Width = 100,
    Height = 100,
    MoveSpeed = 2,
    RotationSpeed = 1
  };

  short int m_Width;
  short int m_Height;
  unsigned char m_RotationSpeed;
  unsigned char m_MoveSpeed;
  std::string m_BodyTexturePath;
  std::string m_TowerTexturePath;
  Type m_Type;
private:
  void setupTankModel();
  friend class Tank;
public:
  TankModel() = default;
  // consider supplying tankType argument with a default value
  TankModel(Type tankType); // resolve this inconvenience as it is not too handy defining private section beforehand.
  std::string TexturePath() const;
  short Height() const;
  short Width() const;
  unsigned char MoveSpeed() const;
  unsigned char RotationSpeed() const;
  std::string TowerTexturePath() const;
};

#endif // TANKMODEL_H
