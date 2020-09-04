#include "mathcore.h"
#include "test_entity_system/controlableentity.h"
#include <iostream>
const double MathCore::m_Pi = std::acos(0.) * 2;

std::pair<double, double> MathCore::getLineMoveCoefficients(const double &angle, double moveSpeed) {
  double dx = moveSpeed * std::sin(degToRad(angle));
  double dy = moveSpeed * std::cos(degToRad(angle));
  return std::pair<double, double>(dx, dy);
}

double MathCore::degToRad(double ang) {
  return m_Pi * ang / 180;
}

double MathCore::radToDeg(double angle)
{
  return angle * 180  / m_Pi;
}

sf::Vertex MathCore::pointOnCircle(const ControlableEntity * entity, double circleRadius, double angle)
{
    double radAngle = degToRad(angle);

    return sf::Vector2f(circleRadius * cos(radAngle),
                        circleRadius * sin(radAngle));
}
