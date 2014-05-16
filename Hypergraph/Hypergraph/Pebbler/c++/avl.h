#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
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