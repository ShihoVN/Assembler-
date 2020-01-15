#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.h"
#include "bt.h"
#include "SymbolT.h"
#include "byteArray.h"

BinaryTree* initializeTree(){
    BinaryTree* bt = createBinaryTree();

    FILE *fp;
    char str[100];
    char* s;

    fp = fopen("readin.txt", "r");
    //printf("START\n");
    while(fgets(str, 100, fp)){
        
        
        s = strtok(str, " ");
        if(strcmp(s, "EOF")==0){
           break;
        }
        //printf("node\n");
        //BTNode* newNode = (BTNode*)malloc( sizeof( BTNode ));
        //newNode->left = NULL;
        //newNode->right = NULL;
        //newNode->syntax = s;
        //printf("%s", newNode->syntax);
        char* index;
        char* hex;

        struct BTNode* newNode = createNewNode(s);
        
        

        for(int i = 0; i<15; i++){
            strcpy(newNode->mode[i], "NULL");
        }

        //printf("syntax %s\n", newNode->syntax);
        index = strtok(NULL, " ");
        //printf("index %s\n", index);
        hex = strtok(NULL, " ");
        //printf(" first hex %s\n", hex);
        //printf("about to get added\n");
        
        while((index != NULL)){
            strcpy(newNode->mode[(atoi(index))], hex);
            //printf("hex %d %s\n", atoi(index), newNode->mode[(atoi(index))] );
            index = strtok(NULL, " ");
            hex = strtok(NULL, " ");

        }
        
        //printf("node finished\n");
        //printf("%s\n", newNode->syntax);
        
        //printf("%s\n", op[0]);
        bt = insertInBinaryTree(bt, newNode);
        //printf("[%s]\n", bt->root->syntax);
    }

    fclose(fp);
    return (bt);

}


BTNode* createNewNode(char* synt){
    struct BTNode* newNode = (BTNode*)malloc( sizeof( BTNode ));
    newNode->left = NULL;
    newNode->right = NULL;
    char* s = (char*)malloc(sizeof(synt));
    strcpy(s, synt);
    newNode->syntax = s;
    
    return newNode;
}

char* getHex(BinaryTree* bt, char* synt, int index){
    printf("gethex function for %s of index %d\n", synt, index);

    if(bt->root== NULL){
        return NULL;
        printf("NULL\n");
    }
    BTNode* current = bt->root;
    printf("starting current node %s\n", current->syntax);
    while(current ){
        //////printf("%s\n", current->syntax);
        if(strcmp(synt, current->syntax)==0){
            printf("found it?\n");
            printf("%s\n", current->syntax);
            if(index == 12 && current->mode[index] == NULL){
                printf("is it null? u tell me");
                index = 6;
            }
            char* hex = (char*)malloc(sizeof(strlen(current->mode[index])));
            if(strcpy(hex, current->mode[index]) == NULL){
                return NULL;
            }
            printf("returning hex value in getHex: %s\n", hex);
            return hex;

        }
        else if(strcmp(bt->root->syntax , synt)<0){
            current = current ->right;
            //printf("moving right\n");
        }
        else{
            current = current ->left;
            //printf("moving left\n");
        }
    }  
    // printf("found it?\n");
    // printf("%s\n", current->syntax);
    // if(index == 12 && current->mode[index] == NULL){
    //     printf("is it null? u tell me");
    //     index = 6;
    // }
    // char* hex = (char*)malloc(sizeof(strlen(current->mode[index])));
    // if(strcpy(hex, current->mode[index]) == NULL){
    //     return NULL;
    // }
    // printf("returning hex value in getHex: %s\n", hex);
    return NULL;

    
} 

int getModeIndex(char* ops){
    /*if(ops == NULL){
        return 0;
    }*/
    if(strcmp(ops, "A")==0){
        return 2;
    }
    /*else if(strchr(ops,'$')== NULL){
        return 12;
    }*/
    else if(strchr(ops,'#')!= NULL){
        return 1;
    }
    else if(strchr(ops,'(')!= NULL){
        if(strchr(ops,'X')!= NULL){
            return 10;
        }
        else if(strchr(ops,'Y')!= NULL){
            return 11;
        }
        else{
            return 9;
        }
    }
    else if(strchr(ops,'X')!= NULL){
        if(strlen(strtok(ops, ",")) > 3){
            return 7;
        }
        else{
            return 4;
        }
    }
    else if(strchr(ops,'Y')!= NULL){
        if(strlen(strtok(ops, ",")) > 3){
            return 8;
        }    
        else{
            return 5;
        }

    }
    else{
        return 3;
    }
}

char* upper(char* syntax){
    char Lsynt[4];
    char Usynt[4];
    strcpy(Lsynt, syntax);
    strcpy(syntax, "");;
    int size = 4;
    printf("ok\n");
    for(int i = 0; i<size; i++){
        Usynt[i] = toupper(Lsynt[i]);
    }
    printf("ayyy%s\n", Usynt);
    return strcpy(syntax, Usynt);
}



