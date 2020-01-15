/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt.h"
#include "syntax.h"
#include "*/

#ifndef BINARYTREE
#define BINARYTREE

#define MAXPRINTBUFFER 500


typedef enum {
    PREORDER,
    INORDER,
    POSTORDER
    } TreeOrder;

typedef struct BTNode {
    char* syntax;
    char mode[15][60];


    struct BTNode* left;
    struct BTNode* right;
} BTNode;

typedef struct BinaryTree {
    BTNode* root;
    int size;
} BinaryTree;

extern BinaryTree* createBinaryTree();
extern BinaryTree* insertInBinaryTree( BinaryTree*, BTNode* );
extern char* toStringBinaryTree( BinaryTree*, TreeOrder );


#endif
