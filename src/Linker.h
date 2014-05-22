#ifndef _LINKER_GUARD
#define _LINKER_GUARD 1

#include <vector>

#include "EdgeAggregator.h"
#include "Molecule.h"

class Linker : public Molecule
{
  public:
    Linker() {}
    ~Linker() {}

    std::vector<EdgeAggregator> Compose(const Molecule&);
    bool Equals(const Molecule&) const;

  private:
};

#endif