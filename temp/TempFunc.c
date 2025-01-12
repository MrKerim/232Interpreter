#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ParseTable.h"
#include "Parser.h"

void add(char* dest, char* src1, char* src2) {
    struct SymbolTable* dEntry = searchInSymbolTable(dest);
    struct SymbolTable* s1Entry = searchInSymbolTable(src1);
    struct SymbolTable* s2Entry = searchInSymbolTable(src2);

    if (dEntry == NULL || s1Entry == NULL || s2Entry == NULL) {
        printf("Error: One of the arrays %s, %s, or %s not found.\n", dest, src1, src2);
        return;
    }

    if (s1Entry->size1 != s2Entry->size1 || s1Entry->size2 != s2Entry->size2) {
        printf("Error: Array sizes do not match for addition.\n");
        return;
    }

    for (int i = 0; i < s1Entry->size1 * (s1Entry->dim == 2 ? s1Entry->size2 : 1); i++) {
        dEntry->base[i] = s1Entry->base[i] + s2Entry->base[i];
    }
}

void sub(char* dest, char* src1, char* src2) {
    struct SymbolTable* dEntry = searchInSymbolTable(dest);
    struct SymbolTable* s1Entry = searchInSymbolTable(src1);
    struct SymbolTable* s2Entry = searchInSymbolTable(src2);

    if (dEntry == NULL || s1Entry == NULL || s2Entry == NULL) {
        printf("Error: One of the arrays %s, %s, or %s not found.\n", dest, src1, src2);
        return;
    }

    if (s1Entry->size1 != s2Entry->size1 || s1Entry->size2 != s2Entry->size2) {
        printf("Error: Array sizes do not match for subtraction.\n");
        return;
    }

    for (int i = 0; i < s1Entry->size1 * (s1Entry->dim == 2 ? s1Entry->size2 : 1); i++) {
        dEntry->base[i] = s1Entry->base[i] - s2Entry->base[i];
    }
}

void mul(char* dest, char* src1, char* src2) {
    struct SymbolTable* dEntry = searchInSymbolTable(dest);
    struct SymbolTable* s1Entry = searchInSymbolTable(src1);
    struct SymbolTable* s2Entry = searchInSymbolTable(src2);

    if (dEntry == NULL || s1Entry == NULL || s2Entry == NULL) {
        printf("Error: One of the arrays %s, %s, or %s not found.\n", dest, src1, src2);
        return;
    }

    if (s1Entry->size1 != s2Entry->size1 || s1Entry->size2 != s2Entry->size2) {
        printf("Error: Array sizes do not match for multiplication.\n");
        return;
    }

    for (int i = 0; i < s1Entry->size1 * (s1Entry->dim == 2 ? s1Entry->size2 : 1); i++) {
        dEntry->base[i] = s1Entry->base[i] * s2Entry->base[i];
    }
}

void div(char* dest, char* src1, char* src2) {
    struct SymbolTable* dEntry = searchInSymbolTable(dest);
    struct SymbolTable* s1Entry = searchInSymbolTable(src1);
    struct SymbolTable* s2Entry = searchInSymbolTable(src2);

    if (dEntry == NULL || s1Entry == NULL || s2Entry == NULL) {
        printf("Error: One of the arrays %s, %s, or %s not found.\n", dest, src1, src2);
        return;
    }

    if (s1Entry->size1 != s2Entry->size1 || s1Entry->size2 != s2Entry->size2) {
        printf("Error: Array sizes do not match for division.\n");
        return;
    }

    for (int i = 0; i < s1Entry->size1 * (s1Entry->dim == 2 ? s1Entry->size2 : 1); i++) {
        if (s2Entry->base[i] == 0) {
            printf("Error: Division by zero at index %d.\n", i);
            return;
        }
        dEntry->base[i] = s1Entry->base[i] / s2Entry->base[i];
    }
}

void* initialize(char name[10], int dim1, int dim2, int value[]){ //dim1, dim2 = operand 1's 1st, 2nd element --- value[] = tempInitArray
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

}

void set(char* name, int value) {
    struct SymbolTable* entry = searchInSymbolTable(name);
    if (entry == NULL) {
        printf("Error: Variable or array %s not found.\n", name);
        return;
    }

    if (entry->dim == 0) {
        // Tek bir değişken
        *(entry->base) = value;
    } else {
        // Dizi elemanları
        for (int i = 0; i < entry->size1 * (entry->dim == 2 ? entry->size2 : 1); i++) {
            entry->base[i] = value;
        }
    }
}

void copy(char* dest, char* src) {
    struct SymbolTable* destEntry = searchInSymbolTable(dest);
    struct SymbolTable* srcEntry = searchInSymbolTable(src);

    if (destEntry == NULL || srcEntry == NULL) {
        printf("Error: One of the arrays %s or %s is not found.\n", dest, src);
        return;
    }

    if (destEntry->size1 != srcEntry->size1 || destEntry->size2 != srcEntry->size2) {
        printf("Error: Array sizes do not match for copy.\n");
        return;
    }

    for (int i = 0; i < destEntry->size1 * (destEntry->dim == 2 ? destEntry->size2 : 1); i++) {
        destEntry->base[i] = srcEntry->base[i];
    }
}

int sum(char* name) {
    struct SymbolTable* entry = searchInSymbolTable(name);
    if (entry == NULL) {
        printf("Error: Array %s not found.\n", name);
        return 0;
    }

    int total = 0;
    for (int i = 0; i < entry->size1 * (entry->dim == 2 ? entry->size2 : 1); i++) {
        total += entry->base[i];
    }
    return total;
}

double average(char* name) {
    struct SymbolTable* entry = searchInSymbolTable(name);
    if (entry == NULL) {
        printf("Error: Array %s not found.\n", name);
        return 0.0;
    }

    int total = sum(name);
    int count = entry->size1 * (entry->dim == 2 ? entry->size2 : 1);
    return (double)total / count;
}

void diag(char* src, char* dest) {
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

void exch(char* src1, int idx1, char* src2, int idx2) {
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

void prt(char* name) {
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