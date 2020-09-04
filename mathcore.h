#ifndef MATHCORE_H
#define MATHCORE_H

#include <cmath>
#include "SFML/Graphics/Vertex.hpp"

class ControlableEntity;

class MathCore
{
public:
  MathCore() = delete;
  static std::pair<double, double> getLineMoveCoefficients(const double &angle, double moveSpeed);
  static sf::Vertex pointOnCircle(const ControlableEntity * entity, double circleRadius, double angle);
  static double degToRad(double ang);
  static double radToDeg(double angle);
private:
  const static double m_Pi;
};

#endif // MATHCORE_H
