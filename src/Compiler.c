#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Compiler.h"
#include "ParseTable.h"
#include "Functions.h"

    /*
    * * Operation codes
        1 addition
        2 subtraction
        3 multiplication
        4 division
        5 initialize
        6 set
        7 copy
        8 sum
        9 average
        10 diagonal
        11 exchange
        12 print
    */

void handleCompile(){
    switch (PT[0].operation)
    {
    case 1:
        //additon
        handleAdditionCompile();
        break;
    
    case 2:
        // subtraction
        handleSubtractionCompile();
        break;
    
    case 3:
        // multiplication
        handleMultiplicationCompile();
        break;
    
    case 4:
        // division
        handleDivisionCompile();
        break; 
    
    case 5:
        // initialize
        handleInitCompile();
        break;

    case 6:
        // set
        handleSetCompile();
        break;
    case 7:
        // copy
        handleCopyCompile();
        break;
    case 8:
        // sum
        handleSumCompile();
        break;
    case 9:
        // average
        break;
    case 10:
        // diagonal
        handleDiagonalCompile();
        break;
    case 11:
        // exchange
        handleExchangeCompile();
        break;
    case 12:
        // print
        handlePrintCompile();
        break;
    default:
        break;
    }
    
}

void handleInitCompile(){
    // PT[0].destination is always the destionaiton
    char *destination = PT[0].destination;
    int dim1 = PT[0].operand1.idx1;
    if(dim1 == -1) dim1 = 0;
    int dim2 = PT[0].operand1.idx2;
    if(dim2 == -1) dim2 = 0;
    if(strcmp(destination,PT[0].operand1.symbol) != 0){
        dim1 = 0;
        dim2 = 0;
    }

    initialize(destination,dim1,dim2,tempInitArray);
}

void handleSetCompile(){
    char *destination = PT[0].destination;
    int val = PT[0].operand1.idx1;
    set(destination, val);
}

void handleCopyCompile(){
    char *dest = PT[0].destination;
    char *src = PT[0].source1;
    copy(dest, src);
}

void handleSumCompile(){
    char *destination = PT[0].destination;
    char *source = PT[0].source1;
    sum(destination, source);
}


void handleDiagonalCompile() {
    diag(PT[0].source1, PT[0].destination);
}

void handleExchangeCompile() {
    printf("Operan symbol : %s\n", PT[0].operand2.symbol);
    exch(PT[0].operand1.symbol, PT[0].operand1.idx1, PT[0].operand2.symbol, PT[0].operand2.idx1);
}

void handlePrintCompile() {
    prt(PT[0].destination);
}

void handleAverageCompile() {
    double avg = average(PT[0].source1);
    set(PT[0].destination, (int)avg); // Cast double to int for simplicity
}

void handleAdditionCompile() {
    add(PT[0].destination, PT[0].source1, PT[0].source2);
}

void handleSubtractionCompile() {
    sub(PT[0].destination, PT[0].source1, PT[0].source2);
}

void handleMultiplicationCompile() {
    mul(PT[0].destination, PT[0].source1, PT[0].source2);
}

void handleDivisionCompile() {
    div(PT[0].destination, PT[0].source1, PT[0].source2);
}