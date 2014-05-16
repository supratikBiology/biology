#ifndef _STDIO_H_
#define _STDIO_H_ 1
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#define _STDLIB_H_ 1
#include <stdlib.h>
#endif

#ifndef _BOOLEAN_
#define _BOOLEAN_ 1
#define FALSE 0
#define TRUE 1
#endif

#define LH -1
#define EH 0
#define RH 1

typedef struct avl_node_type
{
    void *dataPtr;
    struct avl_node_type *left; 
    int bal;
    struct avl_node_type *right;
} AVL_NODE;

typedef struct
{
    int count;
    int (*compare)(void *argu1, void *argu2);
    AVL_NODE *root;
} AVL_TREE;

/*************************************************************************/

/* prototypes */
int AVL_Count(AVL_TREE *tree);
AVL_TREE *AVL_Create(int (*compare) (void *argu1, void *argu2));
AVL_TREE *AVL_Destroy(AVL_TREE *tree);
int AVL_Empty(AVL_TREE *tree);
int AVL_Full(AVL_TREE *node);
int AVL_Insert(AVL_TREE *tree, void *dataInPtr);
void *AVL_Retrieve(AVL_TREE *tree, void *keyPtr);
void AVL_traverse(AVL_TREE *tree, void(*process)(void *dataPtr));
void AVL_traverse_string(AVL_TREE *tree, void(*process)(void *dataPtr, char stringInVisit[]), char stringFromOut[]);