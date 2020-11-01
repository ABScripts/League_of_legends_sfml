#include "mathcore.h"
#include "entity_system/controlableentity.h"
#include "entity_system/scenenode.h"

const double MathCore::m_Pi = std::acos(0.) * 2;

sf::Vector2f MathCore::getLineMoveCoefficients(const double &angle, double moveSpeed) {
  float dx = moveSpeed * std::sin(degToRad(angle));
  float dy = moveSpeed * std::cos(degToRad(angle));
  return {dx, dy};
}

double MathCore::degToRad(double ang) {
  return m_Pi * ang / 180;
}

double MathCore::radToDeg(double angle)
{
  return angle * 180  / m_Pi;
}

sf::Vector2f MathCore::pointOnCircle(const ControlableEntity * entity, double circleRadius, double angle)
{
    double radAngle = degToRad(angle);

    return sf::Vector2f(circleRadius * cos(radAngle) + entity->getOrigin().x ,
                        circleRadius * sin(radAngle) + entity->getOrigin().y);
}

sf::Vector2f MathCore::rotatePoint(sf::Vector2f point, sf::Vector2f around, float _Phi) {
  double Phi = MathCore::degToRad(_Phi);
  float x = (point.x - around.x) * cos(Phi) - (point.y - around.y) * sin(Phi) + around.x;
  float y = (point.x - around.x) * sin(Phi) + (point.y - around.y) * cos(Phi) + around.y;
  return {x, y};
}

void MathCore::buildConvexShape4(const SceneNode &node, Polygon &poly) {
  float angle, W, H;
  sf::Vector2f center, topLeft;

  W = node.width();
  H = node.height();
  center = node.center();
  angle = node.getRotation();
  topLeft = {center.x - W / 2, center.y - H / 2};

  poly.push(rotatePoint({topLeft.x, topLeft.y},         center, angle));
  poly.push(rotatePoint({topLeft.x + W, topLeft.y},     center, angle));
  poly.push(rotatePoint({topLeft.x + W, topLeft.y + H}, center, angle));
  poly.push(rotatePoint({topLeft.x, topLeft.y + H},     center, angle));
}
