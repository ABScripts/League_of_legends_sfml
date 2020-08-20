#include <iostream>
#include "tank.h"
#include "tankmodel.h"
#include "assetmanager.h"
#include "mathcore.h"
#include "tanktowerview.h"

Tank::Tank(TankModel::Type type)
  : m_TankModel(new TankModel(type)),
    m_TowerView(new TankTowerView(m_TankModel->TowerTexturePath()))
{
  m_drawableObjects.push_back(this);
  m_drawableObjects.push_back(m_TowerView);
  setupTank();
}

void Tank::setupTank() {
  setTexture(AssetManager::getTexture(m_TankModel->TexturePath())); // actually setting texture
  setScale(m_TankModel->Width() / static_cast<double>(getTextureRect().width),
           m_TankModel->Height() / static_cast<double>(getTextureRect().height));
  setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
}

const std::vector<const sf::Sprite *> &Tank::drawableObjects() const {
  return m_drawableObjects;
}

void Tank::turnLeft() {
  setRotation(getRotation() - m_TankModel->RotationSpeed());
}

void Tank::turnRight() {
  setRotation(getRotation() + m_TankModel->RotationSpeed());
}

void Tank::turnUp() {
  const auto shift = MathCore::getLineMoveCoefficients(getRotation(), m_TankModel->m_MoveSpeed); // consider changing these lines to more readable ones
  setPosition(getPosition().x + shift.first, getPosition().y - shift.second);
}

void Tank::turnDown() {
  const auto shift = MathCore::getLineMoveCoefficients(getRotation(), m_TankModel->m_MoveSpeed);
  setPosition(getPosition().x - shift.first, getPosition().y + shift.second);
}

