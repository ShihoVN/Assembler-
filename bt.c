#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt.h"
#include "syntax.h"
#include "SymbolT.h"


#include "byteArray.h"

void (*ftable[3])(BTNode*, char*);

BinaryTree* createBinaryTree() {
    BinaryTree* bt = (BinaryTree*)malloc( sizeof( BinaryTree ));

    bt->root = NULL;
    bt->size = 0;
    return( bt );
}



BinaryTree* insertInBinaryTree( BinaryTree* bt, BTNode* nNode) {


    
    //BTNode* nNode = (BTNode*)malloc( sizeof( BTNode ));
    //nNode = newNode;
    //printf("new node inserted %s\n", nNode->syntax);
	if(bt->root == NULL){
		bt->root = nNode;
        //printf("root added %s\n", bt->root->syntax);
        bt->size++;
		return bt;
	}
	//printf("root %s\n", bt->root->syntax);
	int osize = bt->size;
	struct BTNode *temp = bt->root;
	//printf("temp %s\n", temp->syntax);
	while(bt->size == osize){
		if(temp->syntax > nNode->syntax && temp->left == NULL){
			temp->left = nNode;
			bt->size++;
            //printf("added");
		}
		else if(temp->syntax < nNode->syntax && temp->right == NULL){
			temp->right = nNode;
			bt->size++;
            //printf("added");
		}
		else if(temp->syntax> nNode->syntax){
			temp = temp->left;
		}
		else{
			temp = temp->right;
		}
	}
	return bt;
}

char* toStringBinaryTree( BinaryTree* bt, TreeOrder order ) {

    char* printbuf = (char*)malloc( bt->size * 3 );
    if ( bt->root != NULL ) {
        ftable[order]( bt->root, printbuf );
    }
    else{
    return( "nothing left!" );
    }
    return (printbuf);
}


void BinaryTreeInOrder( BTNode* bt, char* p ) {
    char tmpbuf[10];

    if ( bt == NULL )
        return;
    BinaryTreeInOrder( bt->left, p );
    sprintf( tmpbuf, "%s", bt->syntax );
    strcat( p, tmpbuf );
    strcat( p, " " );
    BinaryTreeInOrder( bt->right, p );
}





