#include <stdio.h>
#include <string.h>

#include "ParseTable.h"
#include "Parser.h"



int main() {
    char input[100];

    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, ".end") == 0) break;

        // Parsing input
        Parser(input);

        // Printing ParseTable
        printParseTable();



    }

    printf("End of the program\n");
    
    return 0;
}