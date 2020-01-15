#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt.h"
#include "syntax.h"
#include "SymbolT.h"
#include "byteArray.h"

void insertHex(unsigned char codes[], char* byte, int p){
    codes[p] = (unsigned int)strtol(byte, NULL, 16);
    p++;
    return;
}

void insertOps(unsigned char codes[], char* bytes, int index, int p){
    if(index == 2){
        return;
    }
    else if(index == 1){
        char* substr = malloc(2);
        strncpy(substr, bytes+2, 2);
        codes[p] = (unsigned int)strtol(substr, NULL, 16);
        return;
    }
    else if(index == 6|index == 7|index ==8){
        char* substr = malloc(4);
        strncpy(substr, bytes+1, 4);
        unsigned int hexI = (unsigned int)strtol(substr, NULL, 16);
        unsigned int lastByte = hexI & 0xFF;
        codes[p] = lastByte;
        p++;
        unsigned int firstByte = hexI>>8 & 0xFF;
        codes[p] = firstByte;
        p++;
        return;
    }
    else if(index == 3|index == 4|index ==5){
        char* substr = malloc(2);
        strncpy(substr, bytes+1, 2);
        unsigned int hexI = (unsigned int)strtol(substr, NULL, 16);
        codes[p] = hexI;
        p++;
        return;
    }
    else if(index == 10|index == 11){
        char* substr = malloc(2);
        strncpy(substr, bytes+2, 2);
        unsigned int hexI = (unsigned int)strtol(substr, NULL, 16);
        codes[p] = hexI;
        p++;
        return;
    }
    else if(index == 9){
        char* substr = malloc(4);
        strncpy(substr, bytes+2, 4);
        unsigned int hexI = (unsigned int)strtol(substr, NULL, 16);
        unsigned int lastByte = hexI & 0xFF;
        codes[p] = lastByte;
        p++;
        unsigned int firstByte = hexI>>8 & 0xFF;
        codes[p] = firstByte;
        p++;
        return;
    }

}

void insertAddress(unsigned char codes[], int address, int p, char* starting, int index){
    //if(index == 6){
        int startD = (int)strtol(starting, NULL, 16);
        address = address + startD;
        char* hex;
        sprintf(hex,"%x",address);
        unsigned int hexI = (unsigned int)strtol(hex, NULL, 16);
        unsigned int lastByte = hexI & 0xFF;
        codes[p] = lastByte;
        p++;
        unsigned int firstByte = hexI>>8 & 0xFF;
        codes[p] = firstByte;
        p++;
        return;
    //}
    /*else{
        int startD = (int)strtol(starting, NULL, 16);
        address = address + startD;
        char* hex;
        sprintf(hex,"%x",address);
        unsigned int hexI = (unsigned int)strtol(hex, NULL, 16);
        unsigned int lastByte = hexI & 0xFF;
        codes[p] = lastByte;
        p++;
        unsigned int firstByte = hexI>>8 & 0xFF;
        codes[p] = firstByte;
        p++;
        return;
    }*/
}

void updatePrevAddresses(unsigned char codes[], LL* occurances, char* starting, int p){
    llnode* temp = occurances->head;
    while(temp){
        insertAddress(codes, temp->address, p,starting, 6);
        
        temp = temp->next;
    }
    return;
}