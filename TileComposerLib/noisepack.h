#ifndef NOISEPACK_H
#define NOISEPACK_H

#include <vector>

namespace noise {
namespace module {
class Module;
}
}

struct NoisePack
{
  public:
    std::vector<noise::module::Module*> modules;
    noise::module::Module* main;
};

#endif // NOISEPACK_H
