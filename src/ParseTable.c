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


void clearParseTable(){
    memset(&PT[0], 0, sizeof(struct ParseTable));
}

int tempInitArray[100] = {0};
int stIndex = 0;

struct ParseTable PT[1];
struct SymbolTable ST[20];