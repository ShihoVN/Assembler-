#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt.h"
#include "syntax.h"
#include "SymbolT.h"
#include "byteArray.h"

SymbolTable* createSymbolTable() {
    SymbolTable* st = (SymbolTable*)malloc( sizeof( SymbolTable ));

    st->root = NULL;
    st->size = 0;
    return( st );
}

/*void insertToSymbolTable(SymbolTable st, char* symbol, int boolean, int address){
    if(searchSymbolTable(st, symbol) == NULL){
        Label* lnode = (Label*)malloc(sizeof(Label));
        char* thisSymbol = (char*)malloc(sizeof(char*));
        strcpy(thisSymbol, symbol);
        lnode->label = thisSymbol;
        lnode->address = 0;
        lnode->occurance->head = NULL;
        lnode->right = NULL;
        lnode->left = NULL;
        nodeInsertion(st, lnode);
    }
    if (boolean == 0){
        insertOccurance(searchSymbolTable(st, symbol), address);
        return;
    }
    else{
        insertLabelAddress(searchSymbolTable(st, symbol), address);
        return;
    
    }
}*/

void nodeInsertion(SymbolTable* st, Label* nNode){
    if(st->root == NULL){
		st->root = nNode;
        st->size++;
		return;
	}
	struct Label *temp = st->root;
	while(temp){
		if(strcmp(temp->label, nNode->label)<0 && temp->left == NULL){
			temp->left = nNode;
			st->size++;
            return;
		}
		else if(strcmp(temp->label, nNode->label)>0 && temp->right == NULL){
			temp->right = nNode;
			st->size++;
            return;
		}
		else if(temp->label< nNode->label){
			temp = temp->left;
		}
		else{
			temp = temp->right;
		}
	}

}

Label* initializeInSymbolTable(SymbolTable* st, char* symbol){
    Label* lnode = (Label*)malloc(sizeof(Label));
    //char* thisSymbol = (char*)malloc(sizeof(symbol));
    printf("okay good\n");
    //strcpy(thisSymbol, symbol);
    printf("unique symbol yes\n");
    //printf("here? %s\n", lnode->label);
    lnode->label = (char*)malloc(sizeof(strlen(symbol)));
    strcpy(lnode->label, symbol);
    
    //lnode->address = 0;
    //printf("returning value %d", lnode->address);
    //printf("here?\n");
    lnode->occurance = (LL*)malloc(sizeof(LL*));
    lnode->occurance->head = NULL;
    //printf("here\n");
    lnode->right = NULL;
    lnode->left = NULL;
    printf("here\n");
    nodeInsertion(st, lnode);
    printf("not here\n");
    //free(thisSymbol);
    return lnode;
}


 int insertOccurance(SymbolTable* st, char* symbol, int addr){
    struct Label* lnode = searchSymbolTable(st, symbol);
    if(lnode == NULL){
        printf("ill be so proud\n");
        lnode = initializeInSymbolTable(st, symbol);
    }
    //printf("returning value %d", lnode->address);
    
    llnode* nllnode = (llnode*)malloc(sizeof(llnode));
    nllnode->address = addr;
    nllnode->next = NULL;
    if(lnode->occurance->head == NULL){
        lnode->occurance->head = nllnode;
        lnode->occurance->tail = nllnode;
    }
    else{
        lnode->occurance->tail->next = nllnode;
        lnode->occurance->tail = nllnode;
    }
    printf("so here?\n");
    //printf("returning value %d", lnode->address);
    return lnode->address;
}

LL* insertLabelAddress(SymbolTable* st, char* symbol, int addr){
    printf("called the function!\n");
    struct Label* lnode = searchSymbolTable(st, symbol);
    if(lnode == NULL){
        //printf("new symbooool\n");
        lnode = initializeInSymbolTable(st, symbol);
        printf("yuuuur\n");
    }
    lnode->address = addr;
    if(lnode->occurance->head != NULL){
        return lnode->occurance;
    }
    //printf("word?\n");
    return NULL;
}

Label* searchSymbolTable(SymbolTable* st, char* symbol){
    Label* current = st->root;
    while(current){
        if(strcmp(current->label,symbol) == 0){
            return current;
        }
        else if(strcmp(current->label, symbol)>0){
            current = current->right;
        }
        else{
            current = current->left;
        }
    }
    return NULL;
}

void traversal(FILE* f, Label* root, int start){
    if(root != NULL) {
      traversal(f, root->left, start);
      fprintf(f, "\n"); 
      fprintf(f, "< %s > ",root->label); 
      llnode* temp = root->occurance->head;
      while(temp != NULL)  {
          int addr = start + temp->address;
          fprintf(f, " <%X>",addr);
      }       
      traversal(f, root->right, start);
   }
   return;
}

/*char* tobinary(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

void traversalb(FILE* f, Label* root, int start){
    if(root != NULL) {
      traversal(f, root->left, start);
      fprintf(f, "\n"); 
      fprintf(f, "< %s > ",tobinary(root->label)); 
      llnode* temp = root->occurance->head;
      while(temp != NULL)  {
          int addr = start + temp->address;
          fprintf(f, " <%s>",tobinary(addr));
      }       
      traversal(f, root->right, start);
   }
   return;
}*/



    
    



