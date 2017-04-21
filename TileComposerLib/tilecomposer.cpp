#include "tilecomposer.h"

#include <iostream>

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
  for (int i = 0; i < m_tilesetSize; i++) m_tileset[i] = 0;
}

void TileComposer::copyImageOne(const int x, const int y)
{
  for (int nx = 0; nx < m_tileSize; nx++)
  for (int ny = 0; ny < m_tileSize; ny++)
  {
    m_tileset[ixt(x + nx, y + ny)] = m_one[ixi(nx, ny)];
  }
}

void TileComposer::copyImageTwo(const int x, const int y)
{
  for (int nx = 0; nx < m_tileSize; nx++)
  for (int ny = 0; ny < m_tileSize; ny++)
  {
    m_tileset[ixt(x + nx, y + ny)] = m_two[ixi(nx, ny)];
  }
}

void TileComposer::copyAllImages()
{
  for (int x = 0; x < 3; x++)
  for (int y = 0; y < 3; y++)
  {
    const int x1 = 1 + x + m_tileSize * x;
    const int ny = 1 + y + m_tileSize * y;
    const int x2 = 4 + m_tileSize * (x + 3);
    copyImageOne(x1, ny);
    copyImageTwo(x2, ny);
  }
}

long TileComposer::ixi(const int x, const int y) const
{
  return (x + y * m_tileSize) * 4;
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
}

