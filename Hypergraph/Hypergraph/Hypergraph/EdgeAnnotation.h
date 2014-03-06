#ifndef _EDGE_ANNOTATION_GUARD
#define _EDGE_ANNOTATION_GUARD 1

#include<string>

using namespace std;

//
// This class represents a descriptor applied to an edge of the hypergraph.
// Each axiom, theorem, and definition will have ONE static instance of this class.
//
class EdgeAnnotation
{
  public:
	// The string version of the reason that the edge was created.
	string justification;
	virtual string ToString() const { return justification; }

	bool IsActive() { return active; }

	//
	// Constructors
	//
	EdgeAnnotation();
	EdgeAnnotation(string just, bool active);

  private:
	// Has the user indicated that the use of this edge
	bool active;
};

#endif