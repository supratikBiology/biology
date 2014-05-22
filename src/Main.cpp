#include <vector>
#include <queue>
#include <iostream>

#include "Molecule.h"
#include "Rigid.h"
#include "Linker.h"

#include "HyperGraph.h"
#include "EdgeAnnotation.h"
#include "Instantiator.h"

#include "PebblerHyperGraph.h"

#include "Utilities.h"

int main()
{
    std::vector<Linker> linkers;
    std::vector<Rigid> rigids;
    
    Instantiator instantiator(cout);
    
    HyperGraph<Molecule, EdgeAnnotationT> graph = instantiator.Instantiate(linkers, rigids);

    PebblerHyperGraph<Molecule, EdgeAnnotationT> pebblerGraph = graph.GetPebblerHyperGraph();

    if (DEBUG) cout << graph;

    return 0;
}
