#ifndef MATHCORE_H
#define MATHCORE_H

#include <cmath>

class MathCore
{
public:
  MathCore() = delete;
  static std::pair<double, double> getLineMoveCoefficients(const double &angle, double moveSpeed);
private:
  const static double m_Pi;
};

#endif // MATHCORE_H
