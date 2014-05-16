#ifndef _STDIO_H_
#define _STDIO_H_ 1
#include <stdio.h>
#endif

/*
#ifndef _STDLIB_H_
#define _STDLIB_H_ 1
#include <stdlib.h>
#endif
*/

#ifndef _STRING_H_
#define _STRING_H_ 1
#include <string.h>
#endif

#ifndef _AVL_TYPE_H_
#define _AVL_TYPE_H_1
#include "avl.h"
#endif

#ifndef _HYPER_EDGE_H_
#define _HYPER_EDGE_H_ 1
#include "HyperEdge.h"
#endif

#ifndef _BOOLEAN_
#define _BOOLEAN_ 1
#define FALSE 0
#define TRUE 1
#endif

typedef struct 
{
    void *dataPtr;
    int id;
	AVL_TREE *forwardEdges;
	AVL_TREE *backwardEdges;
} HyperNodeType;

/*************************************************************************/

/* prototypes */

int AddBackwardEdge(HyperNodeType *hNode, HyperEdgeType edge);
int AddForwardEdge(HyperNodeType *hNode, HyperEdgeType edge);
int createHyperNode(void *data, int id, HyperNodeType *hNode);
void destroyHyperNode(HyperNodeType *hNode);
void HyperNodeTypeToString(HyperNodeType hNode, char retString[]);

//public PebblerHyperNode<T, A> CreatePebblerNode();
