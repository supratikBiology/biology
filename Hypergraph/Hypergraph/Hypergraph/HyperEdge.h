#ifndef _HYPEREDGE_GUARD
#define _HYPEREDGE_GUARD 1

#include <vector>
#include <string>

using namespace std;

//
// This class represents both forward and backward edges in the hypergraph.
//
template<class A>
class HyperEdge
{
  public:
	// Allows us to note how the edge was derived
	A annotation;
    vector<int> sourceNodes;
	int targetNode;

	HyperEdge(vector<int> src, int target, A annot);

	// The source nodes and target must be the same for equality.
	virtual bool Equals(HyperEdge<A>& thatEdge);

	//
	// This is an equals method by only providing the many-to-one mapping that defines an edge.
	//
	bool DefinesEdge(vector<int> antecedent, int consequent);
    virtual string ToString();
};

#endif