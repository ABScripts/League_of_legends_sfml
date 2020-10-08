#include "bulletmodel.h"

const std::string BulletModel::mBulletTExturePath = "res/bullet.png";

BulletModel::BulletModel()
  : mHeight(static_cast<int>(Description::Height)),
    mWidth(static_cast<int>(Description::Width)),
    mSpeed(static_cast<int>(Description::Speed)),
    mDamage(static_cast<int>(Description::Damage)),
    mTexturePath(mBulletTExturePath)
{

}

int BulletModel::height() const
{
  return mHeight;
}

int BulletModel::width() const
{
  return mWidth;
}

double BulletModel::speed() const
{
  return mSpeed;
}

std::string BulletModel::texturePath() const
{
  return mTexturePath;
}

int BulletModel::damage() const
{
  return mDamage;
}
