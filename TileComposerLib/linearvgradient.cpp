#include "linearvgradient.h"

#include <algorithm>

LinearVGradient::LinearVGradient(const double &start, const double &middle, const double &stop)
  : m_grow(start, middle),
    m_fade(middle, stop)
{
}

double LinearVGradient::get(const double &val) const
{
  return m_grow.rev(val) + m_fade.get(val);
}

double LinearVGradient::rev(const double &val) const
{
  return 1.0 - get(val);
}
