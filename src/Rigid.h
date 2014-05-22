#ifndef _RIGID_GUARD
#define _RIGID_GUARD 1

#include <vector>

#include "EdgeAggregator.h"
#include "Molecule.h"

class Rigid : public Molecule
{
  public:
    Rigid() {}
    ~Rigid() {}

    std::vector<EdgeAggregator> Compose(const Molecule&);
    bool Equals(const Molecule&) const;

  private:

};

#endif