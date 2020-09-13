#include "tankmodel.h"
#include <tuple>

const TankModel::TexturePaths TankModel::mSelfTexturePath = std::make_pair("res/tankbody.png", "res/tanktower.png");
const TankModel::TexturePaths TankModel::mEnemyTexturePath = std::make_pair("res/tankbody.png", "res/tanktower.png");
const TankModel::TexturePaths TankModel::mTeammateTexturePath= std::make_pair("res/tankbody.png", "res/tanktower.png");

TankModel::TankModel(TankType bodyType, TankType towerType)
  : mWidth(static_cast<int>(Description::Width)),
    mHeight(static_cast<int>(Description::Height)),
    mRotationSpeed(static_cast<int>(Description::RotationSpeed)),
    mMoveSpeed(static_cast<int>(Description::MoveSpeed)),
    mBodyType(bodyType),
    mTowerType(towerType)
{
  setupTankModel();
}

// -------------------------------------------------------
// Sets the appropriative texture path according to the tank`s type
// -------------------------------------------------------
void TankModel::setupTankModel() {
  if (mBodyType == mTowerType) {
      std::tie(mBodyTexturePath, mTowerTexturePath) = switchTextureSets(mBodyType);
    }
  else {
      mBodyTexturePath = switchTextureSets(mBodyType).first;
      mTowerTexturePath = switchTextureSets(mTowerType).second;
    }
}

TankModel::TexturePaths TankModel::switchTextureSets(const TankType & type)
{
  if (type == TankType::Self) {
       return mSelfTexturePath;
    } else if (type == TankType::Teammate) {
        return mTeammateTexturePath;
    } else if (type == TankType::Enemy) {
        return mEnemyTexturePath;
    }
}

// Getter functions

short TankModel::Height() const {
  return mHeight;
}

short TankModel::Width() const {
  return mWidth;
}

unsigned char TankModel::MoveSpeed() const {
  return mMoveSpeed;
}

unsigned char TankModel::RotationSpeed() const {
  return mRotationSpeed;
}

std::string TankModel::towerTexturePath() const
{
  return mTowerTexturePath;
}

std::string TankModel::bodyTexturePath() const
{
  return mBodyTexturePath;
}
