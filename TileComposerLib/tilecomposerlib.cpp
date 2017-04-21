#include "tilecomposerlib.h"

#include "tilecomposer.h"

#include <cstdlib>

void *CreateTileSet(const void *firstImage, const void *secondImage, const long imageSize)
{
  TileComposer composer(imageSize, firstImage, secondImage);
  composer.setTilesetMemory(malloc(composer.size()));

  composer.build();

  return composer.tilesetMemory();
}

void FreeTileSet(void *tileSet)
{
  free(tileSet);
}

long GetTileSetWidth(const long imageSize)
{
  return TileComposer::width(imageSize);
}

long GetTileSetHeight(const long imageSize)
{
  return TileComposer::height(imageSize);
}

