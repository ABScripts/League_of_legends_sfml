#ifndef TANKTOWERMODEL_H
#define TANKTOWERMODEL_H


class TankTowerModel
{
public:
  TankTowerModel();
  short Width() const;
  short Height() const;

private:
  enum class Description {
    Width = 50,
    Height = 140
  };

  short m_Width;
  short m_Height;
};

#endif // TANKTOWERMODEL_H
