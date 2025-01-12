#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Parser.h"
#include "Functions.h"
#include "ParseTable.h"

// 5
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

// 6
void set(char dest[], int value){
    int tempIndex = 0;
    int* tempBase = ST[0].base;

    for(int i = 0; i < 20; i++)
    {
        if(strcmp(dest, ST[i].symbol) == 0)
        {
            tempBase = ST[i].base;
            tempIndex = i;
            break;
        }
    }

    int dim1 = ST[tempIndex].size1;
    int dim2 = ST[tempIndex].size1;
    int totalSize = dim1 * dim2;

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

// 10
void diag(char* src, char* dest){
    struct SymbolTable* srcEntry = searchInSymbolTable(src);
    struct SymbolTable* destEntry = searchInSymbolTable(dest);

    if (srcEntry == NULL) {
        printf("Error: Source array %s not found.\n", src);
        return;
    }

    if (srcEntry->dim != 2 || srcEntry->size1 != srcEntry->size2) {
        printf("Error: Source array must be a square 2D array.\n");
        return;
    }

    if (destEntry == NULL) {
        // Create a new 1D array
        initialize(dest, srcEntry->size1, 0, NULL);
        destEntry = searchInSymbolTable(dest);
    }

    for (int i = 0; i < srcEntry->size1; i++) {
        destEntry->base[i] = srcEntry->base[i * srcEntry->size1 + i];
    }
}

// 11
void exch(char* src1, int idx1, char* src2, int idx2){
    struct SymbolTable* s1Entry = searchInSymbolTable(src1);
    struct SymbolTable* s2Entry = searchInSymbolTable(src2);

    if (s1Entry == NULL || s2Entry == NULL) {
        printf("Error: One of the arrays %s or %s not found.\n", src1, src2);
        return;
    }

    int temp = s1Entry->base[idx1];
    s1Entry->base[idx1] = s2Entry->base[idx2];
    s2Entry->base[idx2] = temp;
}


// 12
void prt(char* name){
    struct SymbolTable* entry = searchInSymbolTable(name);  

    if (entry == NULL) {
        printf("Error: Array %s not found.\n", name);
        return;
    }

    for (int i = 0; i < entry->size1; i++) {
        for (int j = 0; j < (entry->dim == 2 ? entry->size2 : 1); j++) {
            printf("%d ", entry->base[i * entry->size2 + j]);
        }
        printf("\n");
    }
}