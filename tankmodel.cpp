#include "tankmodel.h"
#include <tuple>

const TankModel::TexturePaths TankModel::m_selfTexturePath = std::make_pair("res/tankbody.png", "res/tanktower.png");
const TankModel::TexturePaths TankModel::m_enemyTexturePath = std::make_pair("res/tankbody.png", "res/tanktower.png");
const TankModel::TexturePaths TankModel::m_teammateTexturePath= std::make_pair("res/tankbody.png", "res/tanktower.png");

TankModel::TankModel(Type tankType)
  : m_Height(static_cast<int>(Description::Height)),
    m_Width(static_cast<int>(Description::Width)),
    m_RotationSpeed(static_cast<int>(Description::RotationSpeed)),
    m_MoveSpeed(static_cast<int>(Description::MoveSpeed)),
    m_Type(tankType)
{
  setupTankModel();
}

// -------------------------------------------------------
// Sets the appropriative texture path according to the tank`s type
// -------------------------------------------------------
std::string TankModel::TexturePath() const {
  return m_BodyTexturePath;
}

short TankModel::Height() const {
  return m_Height;
}

short TankModel::Width() const {
  return m_Width;
}

unsigned char TankModel::MoveSpeed() const {
  return m_MoveSpeed;
}

unsigned char TankModel::RotationSpeed() const {
  return m_RotationSpeed;
}

std::string TankModel::TowerTexturePath() const
{
  return m_TowerTexturePath;
}

void TankModel::setupTankModel() {
  TexturePaths texturePaths;
  if (m_Type == Type::Self) {
     texturePaths = m_selfTexturePath;
    } else if (m_Type == Type::Teammate) {
      texturePaths = m_enemyTexturePath;
    } else if (m_Type == Type::Enemy) {
      texturePaths = m_teammateTexturePath;
    }

  std::tie(m_BodyTexturePath, m_TowerTexturePath) = texturePaths;
}
