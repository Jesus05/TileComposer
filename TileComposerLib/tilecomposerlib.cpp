#include "tilecomposerlib.h"

#include <cstdlib>

void *CreateTileSet(const void *firstImage, const void *secondImage, const long imageSize)
{
  const int tileSetSize = GetTileSetWidth(imageSize) * GetTileSetWidth(imageSize) * 4; //W * H * 4(ARGB)
  void *memoryForTileSet = malloc(tileSetSize);
}

void FreeTileSet(void *tileSet)
{
  free(tileSet);
}

long GetTileSetWidth(const long imageSize)
{
  return imageSize * 6 + 7;
}

long GetTileSetHeight(const long imageSize)
{
  return imageSize * 3 + 4;
}

