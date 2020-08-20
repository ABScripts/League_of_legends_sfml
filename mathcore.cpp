#include "mathcore.h"

const double MathCore::m_Pi = std::acos(0.) * 2;

std::pair<double, double> MathCore::getLineMoveCoefficients(const double &angle, double moveSpeed)
{
  double dx = moveSpeed * std::sin(m_Pi * angle / 180);
  double dy = moveSpeed * std::cos(m_Pi * angle / 180);
  return std::pair<double, double>(dx, dy);
}
