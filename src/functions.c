#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Functions.h"
#include "ParseTable.h"


void initialize(char name[10], int dim1, int dim2, int value[]){ //dim1, dim2 = operand 1's 1st, 2nd element --- value[] = tempInitArray
    //
    //Filling the Symbol Table's one element(depends on index of stIndex) with parse table information
    int size = 0;
    int var_check = 0;

    if(dim1 == 0 && dim2 == 0)
    {
        ST[stIndex].dim = 0; // a = 5
        size = 1;
        var_check = 1;
    }else if(dim2 == 0) //one dim array
    {
        ST[stIndex].dim = 1;
        size = dim1;  //arr(5)
    }else{
        ST[stIndex].dim = 2;
        size = dim1 * dim2;
    }

    strcpy(ST[stIndex].symbol, name);

    ST[stIndex].base = (int*) malloc(size*(sizeof(int)));
    
    ST[stIndex].size1 = dim1;
    ST[stIndex].size2 = dim2;

    int* temp_base = ST[stIndex].base;


    // Initializing the variable with the input
    if(var_check)
    {
        *ST[stIndex].base = value[0];
    }else
    {
        for(int i = 0; i < size; i++)   // Initializing the array with the input
        {
            *temp_base = value[i];
            temp_base++;
        }
    }

    stIndex++;

}

void set(char dest[], int value){
    int tempIndex;
    int* tempBase = ST[0].base;

    for(int i = 0; i < 20; i++)
    {
        if(dest == ST[i].symbol)
        {
            tempBase = ST[i].base;
            tempIndex = i;
            break;
        }
    }

    int dim1 = ST[tempIndex].size1;
    int dim2 = ST[tempIndex].size1;
    int totalSize = dim1*dim2;

    if(ST[tempIndex].dim == 0)
    {
        *tempBase = value;

    }else if(totalSize == 0)
    {
        for(int i = 0; i < dim1; i++)
        {
            *tempBase = value;
            tempBase++;
        }
    }else
    {
        for(int i = 0; i < totalSize; i++)
        {
            *tempBase = value;
            tempBase++;
        }
    }
    
}