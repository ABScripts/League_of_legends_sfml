#include <iostream>
#include "tank.h"
#include "tankmodel.h"
#include "assetmanager.h"
#include "mathcore.h"
#include "tanktowerview.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

Tank::Tank(TankModel::Type type)
  : m_TankModel(new TankModel(type)),
    m_TowerView(new TankTowerView(m_TankModel->TowerTexturePath(), m_TankModel->Height() / 2))
{
  attachChild(m_TowerView);
  setupTank();
}

void Tank::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}

void Tank::setupTank() {
  mSprite.setTexture(AssetManager::getTexture(m_TankModel->TexturePath())); // actually setting texture
  mSprite.setScale(m_TankModel->Width() / static_cast<double>(mSprite.getTextureRect().width),
           m_TankModel->Height() / static_cast<double>(mSprite.getTextureRect().height));
  mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2);
}

void Tank::turnLeft(sf::Time time) {
  setRotation(getRotation() - m_TankModel->RotationSpeed() * time.asSeconds());
}

void Tank::turnRight(sf::Time time) {
  setRotation(getRotation() + m_TankModel->RotationSpeed() * time.asSeconds());
}

void Tank::turnUp(sf::Time time) {
  const auto shift = MathCore::getLineMoveCoefficients(getRotation(), m_TankModel->m_MoveSpeed * time.asSeconds()); // consider changing these lines to more readable ones
  setPosition(getPosition().x + shift.first, getPosition().y - shift.second);
}

void Tank::turnDown(sf::Time time) {
  const auto shift = MathCore::getLineMoveCoefficients(getRotation(), m_TankModel->m_MoveSpeed * time.asSeconds());
  setPosition(getPosition().x - shift.first, getPosition().y + shift.second);
}

void Tank::mouseMoved(const std::pair<double, double> & mousePosition)
{
  double angle = atan2(mousePosition.second,
                      mousePosition.first);

  // remembers the last position of mouse when it was moved (products a slight movements)
  // tank->setTrackMousePoint(QPoint(event->x(), event->y()));

  m_TowerView->setRotation(MathCore::degToRad(angle));
}

