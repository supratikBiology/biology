#ifndef _STDIO_H_
#define _STDIO_H_ 1
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#define _STDLIB_H_ 1
#include <stdlib.h>
#endif

#ifndef _ANNOTATION_TYPE_H_
#define _ANNOTATION_TYPE_H_ 1
#include "AnnotationType.h"
#endif

#ifndef PEBBLE_COLORS_
#define PEBBLE_COLORS_ 1
typedef int PebblerColorType;
#define NO_PEBBLE -1
#define RED_FORWARD 0
#define BLUE_BACKWARD 1
#define BLACK_EDGE 2
#define PURPLE_BOTH 3
#endif

#ifndef PebblerHyperEdgeType_
#define PebblerHyperEdgeType_ 1
typedef struct
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
int PebblerHyperEdgeCreate(PebblerHyperEdgeType *e, int *src, int numOfSrc, int target, EdgeAnnotationType annot);
void PebblerHyperEdgeDestroy(PebblerHyperEdgeType *e);
int PebblerHyperEdgeEquals(PebblerHyperEdgeType a, PebblerHyperEdgeType b);
int PebblerHyperEdgeHasNotBeenVisited(PebblerHyperEdgeType e);
int PebblerHyperEdgeIsFullyPebbled(PebblerHyperEdgeType e);
void PebblerHyperEdgeSetColor(PebblerHyperEdgeType *e, PebblerColorType color);
void PebblerHyperEdgeToString(PebblerHyperEdgeType e, char retString[]);