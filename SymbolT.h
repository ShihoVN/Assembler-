/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt.h"
#include "syntax.h"
#include "SymbolT.h"*/

typedef struct Label {
    char* label;
    int address;
    struct LL* occurance;

    struct Label* left;
    struct Label* right;
} Label;

typedef struct SymbolTable {
    Label* root;
    int size;
} SymbolTable;

typedef struct LL{
    struct llnode* head;
    struct llnode* tail;
}LL;
typedef struct llnode{
    int address;
    struct llnode* next;
}llnode;

extern struct SymbolTable* createSymbolTable();
//extern void insertToSymbolTable(SymbolTable*, char*, int, int);
extern struct Label* searchSymbolTable(struct SymbolTable*, char*);
extern void nodeInsertion(struct SymbolTable*, struct Label*);
extern int insertOccurance(struct SymbolTable*, char*, int);
extern LL* insertLabelAddress(struct SymbolTable*, char*, int);
extern Label* initializeInSymbolTable(SymbolTable*, char*);

//extern void traversal(FILE*, Label*, int);
//extern void traversalb(FILE*, Label*, int);
//extern char* tobinary(int);