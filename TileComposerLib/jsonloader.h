#ifndef JSONLOADER_H
#define JSONLOADER_H

class NoisePack;

NoisePack *loadModule(const char *filename);
NoisePack *createModule(const char *json);
void releaseModule(NoisePack *module);

#endif // JSONLOADER_H
