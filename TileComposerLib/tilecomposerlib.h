#ifndef TILECOMPOSERLIB_H
#define TILECOMPOSERLIB_H

#include "tilecomposerlib_global.h"

DLL_EXPORT void* CreateTileSet(const void* firstImage, const long imageSize, const char *JSON);
DLL_EXPORT void* CreateTileSetFromJSONFile(const void* firstImage, const long imageSize, const char *filename);
DLL_EXPORT long GetTileSetWidth(const long imageSize);
DLL_EXPORT long GetTileSetHeight(const long imageSize);
DLL_EXPORT void FreeTileSet(void *tileSet);

#endif // TILECOMPOSERLIB_H
