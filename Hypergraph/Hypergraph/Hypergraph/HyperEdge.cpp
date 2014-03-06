#include <vector>
#include <string>
#include <exception>

#include "HyperEdge.h"

//
// This class represents both forward and backward edges in the hypergraph.
//
template<class A>
HyperEdge<A>::HyperEdge(vector<int> src, int target, A annot)
{
	sourceNodes = src;
    targetNode = target;
	annotation = annot;

	if (src.contains(target))
	{
		throw new exception("There exists a direct cycle in a hyperedge: " + this.ToString());
	}
}

//
// The source nodes and target must be the same for equality.
//
template<class A>
HyperEdge<A>::bool Equals(HyperEdge<A>& thatEdge)
{
	foreach (int src in sourceNodes)
	{
		if (!thatEdge.sourceNodes.Contains(src)) return false;
	}

	return targetNode == thatEdge.targetNode;
}

//
// This is an equals method by only providing the many-to-one mapping that defines an edge.
//
template<class A>
HyperEdge<A>::bool DefinesEdge(vector<int> antecedent, int consequent)
	{
		foreach (int ante in antecedent)
		{
			if (!sourceNodes.Contains(ante)) return false;
		}

		return targetNode == consequent;
	}

	public override int GetHashCode() { return base.GetHashCode(); }

	public override string ToString()
	{
		String retS = " { ";
		foreach (int node in sourceNodes)
		{
			retS += node + ",";
		}
		if (sourceNodes.Count != 0) retS = retS.Substring(0, retS.Length - 1);
		retS += " } -> " + targetNode;
		return retS;
	}
}