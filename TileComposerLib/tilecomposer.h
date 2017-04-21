#ifndef TILECOMPOSER_H
#define TILECOMPOSER_H

#include <vector>

class TileComposer
{
  private:
    long m_tileSize;
    long m_tilesetWidth;
    long m_tilesetSize;
    unsigned char* m_tileset;
    const unsigned char* m_one;
    const unsigned char* m_two;
  public:
    static long width(const long &tileSize);
    static long height(const long &tileSize);
    static long size(const long &tileSize);
  private:
    void clear();
    void copyImage(const int x, const int y, const unsigned char* image);
    void setAlpha(const int x, const int y, const std::vector<std::vector<unsigned char>> &alpha);
    void copyAllImages();
    void setAllAlpha();
    long ixt(const int x, const int y) const;
    long ixi(const int x, const int y) const;
    long imageOneX(const long &x) const;
    long imageTwoX(const long &x) const;
    long imageY(const long &y) const;
  public:
    TileComposer(const long &tileSize, const void* one, const void* two);
    void setTilesetMemory(void* tileset);
    void* tilesetMemory() const;
    long width() const;
    long height() const;
    long size() const;
    void build();

};

#endif // TILECOMPOSER_H
