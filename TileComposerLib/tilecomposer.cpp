#include "tilecomposer.h"

#include "tilepainter.h"

#include <iostream>
#include <cstring>

long TileComposer::width(const long &tileSize)
{
  return tileSize * 6 + 7;
}

long TileComposer::height(const long &tileSize)
{
  return tileSize * 3 + 4;
}

long TileComposer::size(const long &tileSize)
{
  return width(tileSize) * height(tileSize) * 4;
}

void TileComposer::clear()
{
  memset(m_tileset, 0, m_tilesetSize);
}

void TileComposer::copyImage(const int x, const int y, const unsigned char *image)
{
  for (int ny = 0; ny < m_tileSize; ny++)
  {
    memcpy(&m_tileset[ixt(x, y + ny)], &image[ixi(0, ny)], m_tileSize * 4);
  }
}

void TileComposer::setAlpha(const int x, const int y, const std::vector<std::vector<unsigned char> > &alpha)
{
  for (int ny = 0; ny < m_tileSize; ny++)
  for (int nx = 0; nx < m_tileSize; nx++)
  {
    const int index = ixt(x + nx, y + ny);
    m_tileset[index + 3] = alpha[nx][ny];
  }
}

void TileComposer::copyAllImages()
{
  for (int x = 0; x < 3; x++)
  for (int y = 0; y < 3; y++)
  {
    copyImage(imageOneX(x), imageY(y), m_one);
    copyImage(imageTwoX(x), imageY(y), m_two);
  }
}

void TileComposer::setAllAlpha()
{
  TilePainter painter(m_tileSize);

  setAlpha(imageOneX(0), imageY(0), painter.getAlpha(painter.LU));
  setAlpha(imageOneX(1), imageY(0), painter.getAlpha(painter.U));
  setAlpha(imageOneX(2), imageY(0), painter.getAlpha(painter.RU));
  setAlpha(imageOneX(0), imageY(1), painter.getAlpha(painter.L));
//  setAlpha(imageOneX(1), imageY(1), painter.getAlpha(painter.LU));
  setAlpha(imageOneX(2), imageY(1), painter.getAlpha(painter.R));
  setAlpha(imageOneX(0), imageY(2), painter.getAlpha(painter.LD));
  setAlpha(imageOneX(1), imageY(2), painter.getAlpha(painter.D));
  setAlpha(imageOneX(2), imageY(2), painter.getAlpha(painter.RD));

  setAlpha(imageTwoX(0), imageY(0), painter.getAlpha(painter.ILU));
  setAlpha(imageTwoX(1), imageY(0), painter.getAlpha(painter.IU));
  setAlpha(imageTwoX(2), imageY(0), painter.getAlpha(painter.IRU));
  setAlpha(imageTwoX(0), imageY(1), painter.getAlpha(painter.IL));
//  setAlpha(imageTwoX(1), imageY(1), painter.getAlpha(painter.LU));
  setAlpha(imageTwoX(2), imageY(1), painter.getAlpha(painter.IR));
  setAlpha(imageTwoX(0), imageY(2), painter.getAlpha(painter.ILD));
  setAlpha(imageTwoX(1), imageY(2), painter.getAlpha(painter.ID));
  setAlpha(imageTwoX(2), imageY(2), painter.getAlpha(painter.IRD));
}

long TileComposer::ixi(const int x, const int y) const
{
  return (x + y * m_tileSize) * 4;
}

long TileComposer::imageOneX(const long &x) const
{
  return 1 + x + m_tileSize * x;
}

long TileComposer::imageTwoX(const long &x) const
{
  return 4 + x + m_tileSize * (x + 3);
}

long TileComposer::imageY(const long &y) const
{
  return 1 + y + m_tileSize * y;
}

long TileComposer::ixt(const int x, const int y) const
{
  return (x + y * m_tilesetWidth) * 4;
}

TileComposer::TileComposer(const long &tileSize, const void *one, const void *two)
  : m_tileSize(tileSize),
    m_tilesetWidth(width()),
    m_tilesetSize(size(m_tileSize)),
    m_tileset(0),
    m_one(static_cast<const unsigned char*>(one)),
    m_two(static_cast<const unsigned char*>(two))
{
}

void TileComposer::setTilesetMemory(void *tileset)
{
  m_tileset = static_cast<unsigned char*>(tileset);
}

void *TileComposer::tilesetMemory() const
{
  return m_tileset;
}

long TileComposer::width() const
{
  return width(m_tileSize);
}

long TileComposer::height() const
{
  return height(m_tileSize);
}

long TileComposer::size() const
{
  return m_tilesetSize;
}

void TileComposer::build()
{
  if (m_tileset == 0)
  {
    std::cerr << "TILECOMPOSERLIB: Tile set memory not setted! unable to build tileset!";
    return;
  }
  clear();
  copyAllImages();
  setAllAlpha();
}

