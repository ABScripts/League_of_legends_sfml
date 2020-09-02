#include "mathcore.h"

const double MathCore::m_Pi = std::acos(0.) * 2;

std::pair<double, double> MathCore::getLineMoveCoefficients(const double &angle, double moveSpeed) {
  double dx = moveSpeed * std::sin(degToRad(angle));
  double dy = moveSpeed * std::cos(degToRad(angle));
  return std::pair<double, double>(dx, dy);
}

double MathCore::degToRad(int ang) {
  return m_Pi * ang / 180;
}
