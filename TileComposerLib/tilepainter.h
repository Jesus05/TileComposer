#ifndef TILEPAINTER_H
#define TILEPAINTER_H

#include "noise/module/module.h"
#include "lineargradient.h"
#include "linearvgradient.h"

#include <vector>

class TilePainter
{
  public:
    enum EDirection { LU = 1, RU = 2, LD = 4, RD = 8, INNER = 16,
                      R = RU | RD, L = LU | LD, D = RD | LD, U = RU | LU,
                      IRU = INNER | RU, ILU = INNER | LU, IRD = INNER | RD, ILD = INNER | LD,
                      IR = IRU | IRD, IL = ILU | ILD, ID = IRD | ILD, IU = IRU | ILU };

  private:
    const noise::module::Module *m_module;
    int m_tileSize;
    LinearGradient m_gradient;
    LinearVGradient m_vgradient;
    double m_nz;
    bool m_noiseGenerated;

    double nx(const double &x, const EDirection &direction) const;
    double ny(const double &y, const EDirection &direction) const;
    double nz(const double &x, const double &y, const EDirection &direction) const;
    double noise(const double &x, const double &y, const EDirection &direction) const;
    int value(const int &x, const int &y, const EDirection &direction) const;
    double alpha(const double &x, const double &y, const EDirection &direction) const;

  public:
    TilePainter(const int tileSize = 128, const noise::module::Module *m_module = std::nullptr_t());
    ~TilePainter();
//    QImage &setAlpha(const EDirection &direction, QImage &image) const;

    std::vector<std::vector<unsigned char>> getAlpha(const EDirection &direction) const;

    int tileSize() const;

    void update();
};

#endif // TILEPAINTER_H
