#ifndef _STDIO_H_
#define _STDIO_H_ 1
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#define _STDLIB_H_ 1
#include <stdlib.h>
#endif

#ifndef PEBBLER_HYPER_NODE_H_ 
#define PEBBLER_HYPER_NODE_H_ 1
#include "PebblerHyperEdge.h"
#endif

#ifndef PEBBLER_HYPER_NODE_H_ 
#define PEBBLER_HYPER_NODE_H_ 1
#include "PebblerHyperNode.h"
#endif

#ifndef _HYPER_GRAPH_H_
#define _HYPER_GRAPH_H_ 1
#include "HyperGraph.h"
#endif

#ifndef _AVL_TYPE_H_
#define _AVL_TYPE_H_ 1
#include "avl.h"
#endif

#ifndef PEBBLE_COLORS_
#define PEBBLE_COLORS_ 1
typedef int PebblerColorType;
#define NO_PEBBLE -1
#define RED_FORWARD 0
#define BLUE_BACKWARD 1
#define BLACK_EDGE 2
#endif

#ifndef PebblerHyperNodeType_
#define PebblerHyperNodeType_
typedef struct
{
	void *dataPtr;
	int id;
	int pebbled; 
	PebblerColorType pebble;
	int *nodes;
	int numOfNodes;
	AVL_TREE *edges;
} PebblerHyperNodeType;
#endif

typedef struct
{
    AVL_TREE *vertices;
	AVL_TREE *forwardPebbledEdges;
	AVL_TREE *backwardPebbledEdges;
	AVL_TREE *backwardEdgeReachableNodes;
	HyperGraphType *hyperGraph;
}PebblerHyperGraphType;


/*************************************************************************/

/* prototypes */
int PebblerHyperGraphClearPebbles(PebblerHyperGraphType *g);
int PebblerHyperGraphCreate(PebblerHyperGraphType *x, AVL_TREE *vertices);	
void PebblerHyperGraphDestroy(PebblerHyperGraphType *x);
void PebblerHyperGraphGetNode(PebblerHyperGraphType g, int id, PebblerHyperNodeType *retNode);
int PebblerHyperGraphIsNodeNotPebbled(PebblerHyperGraphType g, int id);
int PebblerHyperGraphIsNodePebbledBackward(PebblerHyperGraphType g, int id);
int PebblerHyperGraphIsNodePebbledForward(PebblerHyperGraphType g, int id);
int PebblerHyperGraphNumVertices(PebblerHyperGraphType g);