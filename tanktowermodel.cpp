#include "tanktowermodel.h"


TankTowerModel::TankTowerModel()
  : m_Width(static_cast<int>(Description::Width)),
    m_Height(static_cast<int>(Description::Height))
{

}

short TankTowerModel::Width() const {
  return m_Width;
}

short TankTowerModel::Height() const {
  return m_Height;
}
