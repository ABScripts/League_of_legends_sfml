#ifndef BULLETMODEL_H
#define BULLETMODEL_H

#include <string>

class BulletModel
{
public:
  BulletModel();

  enum class Description {
    Width = 20,
    Height = 20,
    Speed = 550,
    Damage = 200
  };

  int height() const;
  int width() const;
  int damage() const;
  double speed() const;
  std::string texturePath() const;

private:
  static const std::string mBulletTExturePath;

  int mHeight, mWidth;
  int mDamage;
  double mSpeed;
  const std::string mTexturePath;
};

#endif // BULLETMODEL_H
