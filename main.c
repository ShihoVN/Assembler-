#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt.h"
#include "syntax.h"
#include "SymbolT.h"
#include "byteArray.h"

#define START 0
#define END 50

void main(int argc, char* args[]) {

    char* starting = "0";

    //test strtok
    /*
    char* test = (char*)malloc(sizeof(char));
    strcpy(test, "this");
    printf("first %s\n", strtok(test, " "));
    if(strtok(NULL, " ") == NULL){
        printf("null");
    
    }
    */

    //strcpy(test, "this");


    //printf("%s", strchr("$430","$"));
    //printf("ur whole project is shit");
    
    
    BinaryTree* bt = initializeTree();
    /*BTNode* current = bt->root;
    while(current){
        printf("%s\n", current->syntax);
        current = current->right;
    }*/
    SymbolTable* st = createSymbolTable();

    /*
    //getHex works!
    char* test = (char*)malloc(sizeof(char*));
    strcpy(test, "RTS");
    char* hex = getHex(bt, test, 0);
    
    printf("test rts %s\n", hex);
    
   */
    unsigned char codes[300];
    int p = 0x000;


    FILE *fp;
    char str[100];
    //char[1][20];
    
    int index;
    char* s;
    char* line;



    fp = fopen("sieve.asm", "r");
    //printf("START\n");
    while(fgets(str, 100, fp)){
        //printf("NEW LINE\n");
        s = strtok(str, "\n");
        s = strtok(str, ":");
        //printf("%s\n",s);
        line = strtok(NULL, ":");
        //printf("label or na %s\n",line);
        
        
        if(line != NULL){
            printf("recognize label\n");
            LL* prevOccurances = (LL*)malloc(sizeof(LL));
            //printf("here\n");
            char *Label = (char*)malloc(sizeof(s));
            strcpy(Label, s);
            //Label = s;
            //printf("here\n");
            prevOccurances = insertLabelAddress(st, Label, p);
            //printf("okay\n");
            if(prevOccurances != NULL){
                //printf("here?\n");
                updatePrevAddresses(codes, prevOccurances, p);
            }
            //free(prevOccurances);
            
            s = line;
            
        }
        char* command = (char*)malloc(strlen( s));
    
        printf("pls work?\n");
        strcpy(command, s);
        printf("command: %s", command);
        command = strtok(command, ";");
        printf("Command: %s\n", command);
        char* temps = strtok(command, " ");
        char* syntax = (char*)malloc(sizeof(strlen(temps)));
        ////this one has to be in else 
        strcpy(syntax ,temps);
        printf("syntax: %s\n", syntax);
        
        temps = strtok(NULL, " ");
        char* ops = (char*)malloc(sizeof(strlen(temps)));
        if(temps==NULL){
            ops = NULL;
            printf("SYNTAX: %s\n", syntax);
        }
        else{
 
            strcpy(ops ,temps);
            printf("ops: %s\n", ops);
        }
        //  printf("ops: %s\n", ops);


        
       
        
        //strcpy(syntax,upper(syntax));
        //printf("okay?%s\n", upper(syntax));
        //char* ops = strtok(NULL," ");
        
        //printf("%s\n", ops);

        //char* test = "123";
        //printf("%s\n", strchr(test, 4));
        //printf("test%s\n", ops);
        //printf("testing%s\n",strchr(ops,'$'));
        if(ops == NULL){
            printf("are u at least hereeee\n");
            //unsigned char xhex = (unsigned char)malloc(1);
            
            //printf("\nTHE SHIT THATS NOT WORKING XX%sXX\n", syntax);
            char* hex = getHex(bt, syntax, 0);
            if(hex == NULL){
                printf("WHYYYYYYYYYYYYYYYYY\n");
            }
            printf("original hex %s\n", hex);
            //printf("last print tho\n");
            // xhex = (unsigned char)hex;
            // codes[p] = xhex;
            // printf("ADDED SYNTAX in unsigned char %x\n", codes[p]);
            // p++;
            insertHex(codes, hex, p);
        }
        else if(strchr(ops,'$') == NULL){
            printf("why u not here tho\n");
            //index = getModeIndex(ops);
            //unsigned char xhex = (unsigned char*)malloc(1);
            char* hex = getHex(bt, syntax, 12);
            if(hex == NULL){
                printf("WHYYYYYYYYYYYYYYYYY\n");
            }
            printf("last print tho\n");
            insertHex(codes, hex, p);
            printf("last print tho\n");
            //printf("supposed to be in upper%s", upper(s));
            int address = insertOccurance(st, s, p);
            printf("eskeeitttt");
            // unsigned char byteAddress = malloc(1);
            // byteAddress = (unsigned char)address;
            // codes[p] = byteAddress;
            // p++;
            int index = 12;
            BTNode* current = bt->root;
            while(current ){
                if(strcmp(syntax, current->syntax)==0){
                    if(current->mode[12] == NULL){
                        index = 6;
                    }
                }
                else if(strcmp(bt->root->syntax , syntax)<0){
                    current = current ->right;
                }
                else{
                    current = current ->left;
                }
            }
            insertAddress(codes, address, p, starting, index);
        }
        else{
            
            index = getModeIndex(ops);
            //unsigned char xhex = (unsigned char)malloc(1);
            
            
            char* hex = getHex(bt, syntax, index);
            if(hex == NULL){
                printf("WHYYYYYYYYYYYYYYYYY\n");
            }
            printf("original hex %s\n", hex);
            //printf("last print tho\n");
            // xhex = (unsigned char)hex;
            // codes[p] = xhex;
            // printf("ADDED SYNTAX in unsigned char %x\n", codes[p]);
            // p++;
            insertHex(codes, hex, p);
            insertOps(codes, ops, index, p);
        }
        
        

        //DOING RIGHT NOW WITHOUT OPS 
       /* //MAKE SO THAT OPS ARE INSERTTABLE TO ARRAY
        if(index == 1 | index == 3){
            strcpy(codes[p], ops);
            p++;
        }*/


    


    }
    fclose(fp);

    FILE *f = fopen("hex.prt","w");
    fprintf(f, "STARTHEADER\n");
    traversal(f, st->root, atoi(starting));
    fprintf(f, "STARTHEADER\n");
    for(int i = 0; i<300;i++){
        fprintf(f,"%X " , codes[i]);
    }
    fclose(f);
    /*
    FILE *ff = fopen("hex.exc","w");
    fprintf(ff, "STARTHEADER\n");
    traversalb(ff, st->root, atoi(starting));
    fprintf(ff, "STARTHEADER\n");
    for(int i = 0; i<300;i++){
        fprintf(ff,"%s " , codes[i]);
    }
    fclose(ff);
    */

    return;
}
