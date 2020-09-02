#include "tanktowerview.h"
#include "tanktowermodel.h"
#include "assetmanager.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

TankTowerView::TankTowerView(const std::string &towerTexturePath, int shift)
  : m_TowerModel(new TankTowerModel())
{
  setupTower(towerTexturePath, shift);
}

void TankTowerView::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}

void TankTowerView::setupTower(const std::string & towerTexturePath, int shift)
{
  mSprite.setTexture(AssetManager::getTexture(towerTexturePath));
  mSprite.setScale(m_TowerModel->Width() / static_cast<double>(mSprite.getTextureRect().width),
           m_TowerModel->Height() / static_cast<double>(mSprite.getTextureRect().height));
  mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2 + shift);
}
