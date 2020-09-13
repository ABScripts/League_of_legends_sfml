#ifndef TANKTOWERMODEL_H
#define TANKTOWERMODEL_H

#include <string>

class TankTowerModel
{
public:
  TankTowerModel();
  short Width() const;
  short Height() const;
  short rechargeTime() const;

private:
  enum class Description {
    Width = 50,
    Height = 140,
  };

  static double mRechargeTimeSelf;

  double mRechargeTime;
  short m_Width;
  short m_Height;
};

#endif // TANKTOWERMODEL_H
