#include "ParseTable.h"
#include <stdio.h>
#include <string.h>

void printParseTable(){
    printf("#### PARSE TABLE ####\n");
    printf("Operation: %d\n", PT[0].operation);
    printf("Destination: %s\n", PT[0].destination);
    printf("Source1: %s\n", PT[0].source1);
    printf("Source2: %s\n", PT[0].source2);
    printf("Ifexists: %d\n", PT[0].ifexists);
    printf("Condition: %d\n", PT[0].cond);
    printf("Operand1: %s,[%d],[%d]\n", PT[0].operand1.symbol, PT[0].operand1.idx1, PT[0].operand1.idx2);
    printf("Operand2: %s,[%d],[%d]\n", PT[0].operand2.symbol, PT[0].operand2.idx1, PT[0].operand2.idx2);
    printf("tempInitArr: ");
    for(int i = 0; i < 20; i++){
        printf("%d ", tempInitArray[i]);
    }
    printf("\n");

};

void printSymbolTable(){
    printf("#### SYMBOL TABLE ####\n");
    for(int i = 0; i < stIndex; i++){
        printf("Symbol: %s\n", ST[i].symbol);
        printf("Dim: %d\n", ST[i].dim);
        printf("Size1: %d\n", ST[i].size1);
        printf("Size2: %d\n", ST[i].size2);
        printf("Base[0] Int: %d\n", *ST[i].base);
    }
}

void clearParseTable(){
    memset(&PT[0], 0, sizeof(struct ParseTable));
}

int tempInitArray[100] = {0};
int stIndex = 0;

struct ParseTable PT[1];
struct SymbolTable ST[20];