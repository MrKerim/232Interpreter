#ifndef PARSETABLE_H
#define PARSETABLE_H

struct Ary {
char symbol[10];
int idx1; // index 1
int idx2; // index 2
};

struct ParseTable {
int operation; // operation code
char destination[10]; // destination array
char source1[10]; // source array 1
char source2[10]; // source array 2
int ifexists; // 1-exists, 0- does not exist
int cond; // condition code
struct Ary operand1;
struct Ary operand2;
};

struct SymbolTable {
char symbol[10]; // array name
int dim; // array dimension 1 or 2 or 0 (for single variables)
int size1; // array size in dimension 1
int size2; // array size in dimension 2
int *base; // base address for the array
};


void printParseTable();

void printSymbolTable();

void clearParseTable();


extern struct ParseTable PT[1];
extern struct SymbolTable ST[20];

// Testing
extern int tempInitArray[100];
extern int stIndex;





#endif
