#ifndef _STDIO_H_
#define _STDIO_H_ 1
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#define _STDLIB_H_ 1
#include <stdlib.h>
#endif

#ifndef _AVL_TYPE_H_
#define _AVL_TYPE_H_ 1
#include "avl.h"
#endif

#ifndef _HYPER_EDGE_H_
#define _HYPER_EDGE_H_ 1
#include "HyperEdge.h"
#endif

#ifndef PEBBLER_HYPER_NODE_H_ 
#define PEBBLER_HYPER_NODE_H_ 1
#include "PebblerHyperEdge.h"
#endif

#ifndef PEBBLE_COLORS_
#define PEBBLE_COLORS_ 1
#define NO_PEBBLE -1
#define RED_FORWARD 0
#define BLUE_BACKWARD 1
#define BLACK_EDGE 2
#define PURPLE_BOTH 3
typedef int PebblerColorType;
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

#ifndef PebblerHyperEdgeType_
#define PebblerHyperEdgeType_ 1						
typedef struct					/* I don't know why, but if this typedef isn't in this file, there is an error, even though PebblerHyperEdge.h is included in this file.*/
{
	int *sourceNodes;
	int numOfSourceNodes;
	int targetNode;
	EdgeAnnotationType annot;
	int *sourcePebbles;
	int numOfSourcePebbles;
	PebblerColorType pebbleColor;
	int pebbles;
} PebblerHyperEdgeType;
#endif

/*************************************************************************/

/* prototypes */
int PebblerHyperNodeAddEdge(PebblerHyperNodeType *n, PebblerHyperEdgeType *e);
int PebblerHyperNodeAddEdgeSourceTarget(PebblerHyperNodeType *n, EdgeAnnotationType annot, int *sourceNodes, int numOfSourceNodes, int targetNode);
int PebblerHyperNodeCreate(PebblerHyperNodeType *n, void *dataPtr, int id);
void PebblerHyperNodeDestroy(PebblerHyperNodeType *n);
void PebblerHyperNodeToString(PebblerHyperNodeType hEdge, char retString[]);