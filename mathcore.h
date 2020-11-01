#ifndef MATHCORE_H
#define MATHCORE_H

#include <cmath>
#include "SFML/Graphics/Vertex.hpp"
#include "polygon.h"

class SceneNode;

class ControlableEntity;

class MathCore
{
public:
  MathCore() = delete;
  static sf::Vector2f getLineMoveCoefficients(const double &angle, double moveSpeed);
  static sf::Vector2f pointOnCircle(const ControlableEntity * entity, double circleRadius, double angle);
  static double degToRad(double ang);
  static double radToDeg(double angle);
  static sf::Vector2f rotatePoint(sf::Vector2f point, sf::Vector2f around, float _Phi);
  static void buildConvexShape4(const SceneNode &node, Polygon &poly);
private:
  const static double m_Pi;
};

#endif // MATHCORE_H
