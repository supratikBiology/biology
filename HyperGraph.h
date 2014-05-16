#ifndef _STDIO_H_
#define _STDIO_H_ 1
#include <stdio.h>
#endif

#ifndef _HYPER_NODE_H_
#define _HYPER_NODE_H_ 1
#include "HyperNode.h"
#endif

#ifndef _HYPER_EDGE_H_
#define _HYPER_EDGE_H_ 1
#include "HyperEdge.h"
#endif

#ifndef _AVL_TYPE_H_
#define _AVL_TYPE_H_ 1
#include "avl.h"
#endif

typedef struct
{
    /* list of Hypernodes */
	AVL_TREE *vertices;
}HyperGraphType;


/*************************************************************************/

/* prototypes */
int createHyperGraph(HyperGraphType *g);
int hyperGraphAddForwardEdge(HyperGraphType *h, int sourceNodes[], int sourceNodeCount, int targetNode, EdgeAnnotationType annot);
int hyperGraphAddNode(HyperGraphType *h, HyperNodeType *x);
void *hyperGraphGetNode(HyperGraphType *h, HyperNodeType *x);
int hyperGraphGetNodeFromId(HyperGraphType *h, int id, HyperNodeType *n);
int hyperGraphHasForwardEdge(HyperGraphType *h, int sourceNodes[], int sourceNodeCount, int targetNode);
int hyperGraphSize(HyperGraphType *g);