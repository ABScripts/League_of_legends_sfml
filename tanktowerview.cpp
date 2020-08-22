#include "tanktowerview.h"
#include "tanktowermodel.h"
#include "assetmanager.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

TankTowerView::TankTowerView(const std::string &towerTexturePath)
  : m_TowerModel(new TankTowerModel())
{
  setupTower(towerTexturePath);
}

void TankTowerView::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}

void TankTowerView::setupTower(const std::string & towerTexturePath)
{
  mSprite.setTexture(AssetManager::getTexture(towerTexturePath));
  mSprite.setScale(m_TowerModel->Width() / static_cast<double>(mSprite.getTextureRect().width),
           m_TowerModel->Height() / static_cast<double>(mSprite.getTextureRect().height));
}
