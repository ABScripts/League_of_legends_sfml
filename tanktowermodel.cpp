#include "tanktowermodel.h"

double TankTowerModel::mRechargeTimeSelf = 1.25;

TankTowerModel::TankTowerModel()
  : m_Width(static_cast<int>(Description::Width)),
    m_Height(static_cast<int>(Description::Height)),
    mRotationSpeed(static_cast<int>(Description::RotationSpeed)),
    mRechargeTime(mRechargeTimeSelf)
{

}

short TankTowerModel::Width() const {
  return m_Width;
}

short TankTowerModel::Height() const {
  return m_Height;
}

short TankTowerModel::rechargeTime() const
{
  return mRechargeTime;
}

short TankTowerModel::rotationSpeed() const
{
  return mRotationSpeed;
}
