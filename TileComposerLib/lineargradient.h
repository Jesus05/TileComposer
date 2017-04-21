#ifndef LINEARGRADIENT_H
#define LINEARGRADIENT_H


class LinearGradient
{
  private:
    double m_start;
    double m_stop;
    double m_step;
  public:
    LinearGradient(const double &start, const double &stop);
    double get(const double &val) const;
    double rev(const double &val) const;
    double get(const double &val, const double &noise) const;
    double rev(const double &val, const double &noise) const;
};

#endif // LINEARGRADIENT_H
