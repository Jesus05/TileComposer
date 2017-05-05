#include "tilecomposerlib.h"

#include "tilecomposer.h"

#include <cstdlib>

#include "noisepack.h"
#include "jsonloader.h"

void *CreateTileSet(const void *firstImage, const long imageSize, const char *JSON)
{
  TileComposer composer(imageSize, firstImage);
  composer.setTilesetMemory(malloc(composer.size()));
  NoisePack *pack = createModule(JSON);
  if (pack) composer.setNoise(pack->main);

  composer.build();

  void* ret = composer.tilesetMemory();

  releaseModule(pack);

  return ret;
}

void *CreateTileSetFromJSONFile(const void* firstImage, const long imageSize, const char *filename)
{
  TileComposer composer(imageSize, firstImage);
  composer.setTilesetMemory(malloc(composer.size()));
  NoisePack *pack = loadModule(filename);
  if (pack) composer.setNoise(pack->main);

  composer.build();

  void* ret = composer.tilesetMemory();

  releaseModule(pack);

  return ret;
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

