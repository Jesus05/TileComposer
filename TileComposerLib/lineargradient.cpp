#include "lineargradient.h"

#include <algorithm>

LinearGradient::LinearGradient(const double &start, const double &stop)
  : m_start(start),
    m_stop(stop),
    m_step(1.0 / (m_stop - m_start))
{
}

double LinearGradient::get(const double &val) const
{
  if (val <= m_start) return 0.0;
  if (val >= m_stop) return 1.0;
  return (val - m_start) * m_step;
}

double LinearGradient::rev(const double &val) const
{
  return 1.0 - get(val);
}

double LinearGradient::get(const double &val, const double &noise) const
{
  return std::min(1.0, std::max(0.0, noise + get(val)));
}

double LinearGradient::rev(const double &val, const double &noise) const
{
  return std::min(1.0, std::max(0.0, noise + rev(val)));
}
