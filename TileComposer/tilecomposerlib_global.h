#ifndef TILECOMPOSERLIB_GLOBAL_H
#define TILECOMPOSERLIB_GLOBAL_H

#if defined(_WIN32) || defined(__WIN32__)

  #if defined(TILE_COMPOSER_EXPORT)

    #define  DLL_EXPORT extern "C" __declspec(dllexport)
  #else

    #define  DLL_EXPORT extern "C" __declspec(dllimport)

  #endif /* TILE_COMPOSER_EXPORT */

#elif defined(linux) || defined(__linux)

  #define DLL_EXPORT

#endif

#endif // TILECOMPOSERLIB_GLOBAL_H
