#ifndef TILECOMPOSER_H
#define TILECOMPOSER_H


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
    void copyImageOne(const int x, const int y);
    void copyImageTwo(const int x, const int y);
    void copyAllImages();
    long ixt(const int x, const int y) const;
    long ixi(const int x, const int y) const;
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
