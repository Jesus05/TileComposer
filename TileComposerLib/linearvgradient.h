#ifndef LINEARVGRADIENT_H
#define LINEARVGRADIENT_H

#include "lineargradient.h"

class LinearVGradient
{
  private:
    LinearGradient m_grow;
    LinearGradient m_fade;
  public:
    LinearVGradient(const double &start, const double &middle, const double &stop);
    double get(const double &val) const;
    double rev(const double &val) const;
};

#endif // LINEARVGRADIENT_H
