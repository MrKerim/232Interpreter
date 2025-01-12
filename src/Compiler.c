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
        break;
    
    case 2:
        // subtraction

        break;
    
    case 3:
        // multiplication

        break;
    
    case 4:
        // division

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
        break;
    case 8:
        // sum
        break;
    case 9:
        // average
        break;
    case 10:
        // diagonal
        break;
    case 11:
        // exchange
        break;
    case 12:
        // print
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