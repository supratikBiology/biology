#ifndef _STDIO_H_
#define _STDIO_H_ 1
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#define _STDLIB_H_ 1
#include <stdlib.h>
#endif

#ifndef _STRING_H_
#define _STRING_H_ 1
#include <string.h>
#endif

#ifndef _HYPEREDGE_GUARD
#define _HYPEREDGE_GUARD 1

typedef struct
{
	char justification[100];
    int active;
} EdgeAnnotationType;

typedef struct
{
    int targetNodes;
	int *sourceNodes;
	EdgeAnnotationType annotation;
	int sourceCount;
}HyperEdgeType;

/*************************************************************************/

/* prototypes */
void EdgeAnnotation_createEdgeAnnotation(char just[], int active, EdgeAnnotationType *ret);
int EdgeAnnotation_isActive(EdgeAnnotationType *ea);
int HyperEdge_create(int src[], int target, EdgeAnnotationType annot, int sourceCount, HyperEdgeType *hEdge);
int HyperEdge_definesEdge(int antecedent[], int consequent, int antecedentLength, HyperEdgeType hEdge);
void HyperEdge_destroy(HyperEdgeType *hEdge);
int HyperEdge_equals(HyperEdgeType a, HyperEdgeType b);
void HyperEdge_toString(HyperEdgeType hEdge, char retString[]);

#endif