#include "tanktowerview.h"
#include "tanktowermodel.h"
#include "assetmanager.h"

TankTowerView::TankTowerView(const std::string &towerTexturePath)
  : m_TowerModel(new TankTowerModel())
{
  setupTower(towerTexturePath);
}

void TankTowerView::setupTower(const std::string & towerTexturePath)
{
  setTexture(AssetManager::getTexture(towerTexturePath));
  setScale(m_TowerModel->Width() / static_cast<double>(getTextureRect().width),
           m_TowerModel->Height() / static_cast<double>(getTextureRect().height));
}
