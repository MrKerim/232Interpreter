#include <stdio.h>
#include <string.h>

#include "ParseTable.h"
#include "Parser.h"
#include "Functions.h"
#include "Compiler.h"



int main() {
    char input[100];

    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, ".end") == 0) break;
        if (strcmp(input, ".showPT") == 0) {
            printParseTable();
            printSymbolTable();
            continue;
        }

        // Parsing input
        Parser(input);

        // Executing the operation
        handleCompile();

       

    }

    printf("End of the program\n");
    
    return 0;
}