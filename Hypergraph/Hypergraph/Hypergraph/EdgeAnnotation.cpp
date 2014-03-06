#include "EdgeAnnotation.h"

//
// This class represents a descriptor applied to an edge of the hypergraph.
// Each axiom, theorem, and definition will have ONE static instance of this class.
//
EdgeAnnotation::EdgeAnnotation() : justification(""), active(false) {}

EdgeAnnotation::EdgeAnnotation(string just, bool act) : justification(just), active(act) {}