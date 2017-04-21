#include "tilepainter.h"

#include "noise/module/perlin.h"

double TilePainter::nx(const double &x, const TilePainter::EDirection &direction) const
{
  double ret = (double)x / (double)m_tileSize;
  switch (direction)
  {
    case U:
    case D:
    case IU:
    case ID:
      if (x < m_tileSize / 2.0) return ret;
      else return 0.5 + (0.5 - ret);
    case R:
    case RU:
    case RD:
    case IR:
    case IRU:
    case IRD:
      return ret;
    case L:
    case LU:
    case LD:
    case IL:
    case ILU:
    case ILD:
      return ret - 1.0;
    case INNER:
      return 0;
  }

  return ret;
}

double TilePainter::ny(const double &y, const TilePainter::EDirection &direction) const
{
  double ret = (double)y / (double)m_tileSize;

  switch (direction)
  {
    case R:
    case L:
    case IR:
    case IL:
      if (y < m_tileSize / 2.0) return ret;
      else return 0.5 + (0.5 - ret);
    case U:
    case RU:
    case LU:
    case IU:
    case IRU:
    case ILU:
      return ret - 1.0;
    case D:
    case RD:
    case LD:
    case ID:
    case IRD:
    case ILD:
      return ret;
    case INNER:
      return 0;
  }

  return ret;
}

double TilePainter::nz(const double &/*x*/, const double &/*y*/, const TilePainter::EDirection &/*direction*/) const
{
  return m_nz;
}

double TilePainter::noise(const double &x, const double &y, const TilePainter::EDirection &direction) const
{
  const double val = m_module->GetValue(nx(x, direction), ny(y, direction), nz(x, y, direction)) / 2.0; //Real return values from -1.9 to 1.9
  return val;
}

int TilePainter::value(const int &x, const int &y, const TilePainter::EDirection &direction) const
{
  const int mx = (direction & R) ? x : (m_tileSize - x);
  const int my = (direction & D) ? y : (m_tileSize - y);

  switch (direction)
  {
    case R:
    case L:
    case IR:
    case IL:
      return mx;
    case U:
    case D:
    case IU:
    case ID:
      return my;
    case RD:
    case LD:
    case RU:
    case LU:
    case IRD:
    case ILD:
    case IRU:
    case ILU:
      return sqrt(mx*mx + my*my);
    case INNER:
      return 0;
  }
  return 0;
}

double TilePainter::alpha(const double &x, const double &y, const TilePainter::EDirection &direction) const
{
  const double val = value(x, y, direction);
  double alpha = m_gradient.get(val, noise(x, y, direction) * m_vgradient.rev(val)) * 255.0;
//  if (direction & INNER) alpha = m_gradient.rev(val, -noise(x, y, direction) * m_vgradient.rev(val)) * 255.0;
//  else alpha = m_gradient.get(val, noise(x, y, direction) * m_vgradient.rev(val)) * 255.0;
  if (direction & INNER) alpha = 255.0 - alpha;
  return alpha;
}

TilePainter::TilePainter(const int tileSize)
  : m_tileSize(tileSize),
    m_gradient(m_tileSize / 3.0, m_tileSize * 2.0 / 3.0),
    m_vgradient(m_tileSize / 6.0, m_tileSize / 2.0, m_tileSize * 5.0 / 6.0)
{
  noise::module::Perlin *perlin = new noise::module::Perlin();
  perlin->SetOctaveCount(3);
  perlin->SetFrequency(2);

  m_nz = 0.0;

  m_module = perlin;
}

int TilePainter::tileSize() const
{
  return m_tileSize;
}

void TilePainter::update()
{
//  noise::module::Perlin *perlin = static_cast<noise::module::Perlin*>(m_module);
//  perlin->SetSeed(perlin->GetSeed() + 1);
  m_nz += 0.05;
}

//QImage &TilePainter::setAlpha(const TilePainter::EDirection &direction, QImage &image) const
//{
//  if (image.width() != m_tileSize || image.height() != m_tileSize)
//  {
//    qDebug() << image;
//    qWarning("Image not valid size");
//    return image;
//  }

//  for (int x = 0; x < m_tileSize; x++)
//  for (int y = 0; y < m_tileSize; y++)
//  {
//    QColor color = image.pixelColor(x, y);
//    color.setAlpha(alpha(x, y, direction));
//    image.setPixelColor(x, y, color);
//  }

//  return image;
//}

std::vector<std::vector<unsigned char> > TilePainter::getAlpha(const TilePainter::EDirection &direction) const
{
  std::vector<unsigned char> emptyLine(m_tileSize, 0);
  std::vector<std::vector<unsigned char>> ret(m_tileSize, emptyLine);

  for (int x = 0; x < m_tileSize; x++)
  for (int y = 0; y < m_tileSize; y++)
  {
    ret[x][y] = alpha(x, y, direction);
  }

  return ret;
}
