#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Parser.h"
#include "ParseTable.h"


/*
* * Notes
*
    If; if operand is an integer symbol will be \0 and idx1 will be the integer value
    if( 5 < A[2]) -> operand1.symbol = "\0", operand1.idx1 = 5 , operan2.symbol = "A", operand2.idx1 = 2 operand2.idx2 = -1

    in expression we can't have any operands
    we can only have if(condtional) A = B + C not A = B[2] + C[2];


* 
*/


void Parser(char *input) {

    clearParseTable();
    
    char** res = seperateIFandExpression(input);
    char *ifClause = res[0]; char *expression = trim(res[1]);
    
    handleIFStatementParsing(ifClause);
    handleExpressionParsing(expression);

}

char* trim(char* str){

    while (*str && isspace((unsigned char)*str)) str++;

    if (*str) {
        char* end = str + strlen(str) - 1;
        while (end > str && isspace((unsigned char)*end)) end--;
        *(end + 1) = '\0';
    }

    return str;
}

char** seperateIFandExpression(char *input){

    char temp[100];
    strcpy(temp,input);

    char *expression = input;
    char *conditional = trim(strtok(temp,"("));

    if(strcmp(conditional,"if")==0) conditional = strtok(NULL,")");
    else conditional = NULL;

    if(conditional != NULL) expression = strtok(NULL,"\0");

    char **result = malloc(2 * sizeof(char*));

    result[0] = conditional ? strdup(conditional) : NULL;
    result[1] = expression ? strdup(expression) : NULL;
    return result;
}

int getConditionCode(char* input){

    /*
    # Condition Codes
    1 ==
    2 !=
    3 >
    4 >=
    5 <
    6 <=
    */

    if(strstr(input,"==")) return 1;
    if(strstr(input,"!=")) return 2;
    if(strstr(input,">=")) return 4;
    if(strstr(input,"<=")) return 6;
    if(strstr(input,">")) return 3;
    if(strstr(input,"<")) return 5;
    else return 0;
}

void handleIFStatementParsing(char* ifClause){
    
    if(ifClause == NULL) return;
    ifClause = trim(ifClause);

    PT[0].ifexists = 1;
    PT[0].cond = getConditionCode(ifClause);

    char *operand1 = strtok(ifClause,"<=>!=");
    char *operand2 = strtok(NULL,"\0");
    if(!(PT[0].cond == 3 || PT[0].cond == 5)) operand2++;

    operand1 = trim(operand1); operand2 = trim(operand2);

    PT[0].operand1 = tokenizeOperand(operand1);
    PT[0].operand2 = tokenizeOperand(operand2);

}

struct Ary tokenizeOperand(char* operand){
    struct Ary result;

    if(!strchr(operand,'[') && !strchr(operand,'(')){
        // integer
        if(isInteger(operand)){
            result.symbol[0] = '\0';
            result.idx1 = atoi(operand);
            result.idx2 = -1;
        }

        // single variable
        else{
            strcpy(result.symbol,operand);
            result.idx1 = -1;
            result.idx2 = -1;
        }
    }
    
    else if(strchr(operand,'(')){
               // array init ..()
        char *opName = trim(strtok(operand,"("));
        strcpy(result.symbol,opName);
    
        char *index = trim(strtok(NULL,")"));
        // Two dimensional array
        if(strchr(index,',')){
            char *idx1 = trim(strtok(index,","));
            char *idx2 = trim(strtok(NULL,"\0"));
            result.idx1 = atoi(idx1);
            result.idx2 = atoi(idx2);
        }
        // Single dimensional array
        else{
            result.idx1 = atoi(index);
            result.idx2 = -1;
        }
    }
    
    else{

        // array subscript ..[]
        char *opName = trim(strtok(operand,"["));
        strcpy(result.symbol,opName);
    
        char *index = trim(strtok(NULL,"]"));
        // Two dimensional array
        if(strchr(index,',')){
            char *idx1 = trim(strtok(index,","));
            char *idx2 = trim(strtok(NULL,"\0"));
            result.idx1 = atoi(idx1);
            result.idx2 = atoi(idx2);
        }
        // Single dimensional array
        else{
            result.idx1 = atoi(index);
            result.idx2 = -1;
        }
    }

    return result;

}

int isInteger(const char* str) {
    char *endptr;
    strtol(str, &endptr, 10);
    return *endptr == '\0';
}

void handleExpressionParsing(char* expression){
    /*
    * * Operation codes
        #uses '='
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
        
        # uses '<>'
        11 exchange

        # uses no speaial operand
        12 print
    */

    // print function
    if(strchr(expression,'=') == NULL && strstr(expression,"<>") == NULL){
        handlePrintFunctionParsing(expression);
        return;
    }

    // excahnge
    if(strchr(expression,'=') == NULL){
        handleExchangeFunctionParsing(expression);
        return;
    }

    // arithmetic operation
    if(!(strchr(expression,'+') == NULL && strchr(expression,'-') == NULL &&
     strchr(expression,'*') == NULL && strchr(expression,'/') == NULL)){

        handleArithmeticOperationParsing(expression);
        return;
    }




    // initialize, set, copy or sum, average, diagonal
    char* leftHandSide = trim(strtok(expression,"="));
    char* rightHandSide = trim(strtok(NULL,"\0"));

    if( strstr(rightHandSide,"sum") != NULL || strstr(rightHandSide,"aver") != NULL ||
    strstr(rightHandSide,"diag") != NULL){
    // sum, average, diagonal
    handleSumAvarageDiagonalParsing(rightHandSide,leftHandSide);
        return;
    }

    // initialize, set, copy
    // For theese three wee need ST to check if a va exist or is it array
    // or a single variable

    // initialize array
    if(strchr(leftHandSide,'(')){
        handleInitializeArrayParsing(leftHandSide,rightHandSide);
        return;
    }

    // there is a single var in the left hand side (A = or X = ...)
    struct SymbolTable* sTEntry = searchInSymbolTable(leftHandSide);

    if(sTEntry == NULL){
        // init a single variable
        handleInitASingleVariable(leftHandSide,rightHandSide);
        return;
    }

    // set or copy , set uses integer 
    handleSetOrCopyFunctionParsing(leftHandSide,rightHandSide);


    return;

}

void handleArithmeticOperationParsing(char* expression){


    char* destination = trim(strtok(expression,"="));
    strcpy(PT[0].destination,destination);
    expression = strtok(NULL,"\0");

    if(strchr(expression,'+') != NULL) PT[0].operation = 1;
    else if(strchr(expression,'-') != NULL) PT[0].operation = 2;
    else if(strchr(expression,'*') != NULL) PT[0].operation = 3;
    else if(strchr(expression,'/') != NULL) PT[0].operation = 4;

    char* source1 = tokenizeOperand(trim(strtok(expression,"+-*/"))).symbol;
    char* source2 = tokenizeOperand(trim(strtok(NULL,"\0"))).symbol;

    strcpy(PT[0].source1,source1);
    strcpy(PT[0].source2,source2);

}

void handleExchangeFunctionParsing(char* expression){

        char* destination = trim(strtok(expression,"<>"));
        char* source = trim(strtok(NULL,"\0"));
        source++;

        PT[0].operation = 11;
        PT[0].operand1 = tokenizeOperand(destination);
        PT[0].operand2 = tokenizeOperand(source);

        strcpy(PT[0].destination,PT[0].operand1.symbol);
        strcpy(PT[0].source1,PT[0].operand2.symbol);
}

void handlePrintFunctionParsing(char* expression){
        char* source = strtok(expression,"(");
        source = strtok(NULL,")");
        
        PT[0].operation = 12;
        strcpy(PT[0].destination,source);
}

void handleSumAvarageDiagonalParsing(char* rightHandSide, char* leftHandSide){

            if(strstr(rightHandSide,"sum") != NULL) PT[0].operation = 8;
            else if(strstr(rightHandSide,"aver") != NULL) PT[0].operation = 9;
            else if(strstr(rightHandSide,"diag") != NULL) PT[0].operation = 10;

            rightHandSide = strtok(rightHandSide,"(");
            rightHandSide = strtok(NULL,")");

            strcpy(PT[0].source1,rightHandSide);
            strcpy(PT[0].destination,leftHandSide);
}

void handleInitializeArrayParsing(char* leftHandSide, char* rightHandSide){
    
        PT[0].operation = 5;
        PT[0].operand1 = tokenizeOperand(leftHandSide);
        strcpy(PT[0].destination,PT[0].operand1.symbol);

        //[2,3...] or [[2,3,4],[1,2..],[4,5,6..]]
        
        int i = 0;
        char* token = strtok(rightHandSide,",]");
        while (token != NULL)
        {
            while (*token == '[' || *token == ',' || *token == ' ') token++;
            tempInitArray[i++] = atoi(token);
            token = strtok(NULL,",]");              
        }
        
}

void handleInitASingleVariable(char* leftHandSide, char* rightHandSide){
    PT[0].operation = 5;
    strcpy(PT[0].destination,trim(leftHandSide));
    tempInitArray[0] = atoi(trim(rightHandSide));
}

void handleSetOrCopyFunctionParsing(char* leftHandSide, char* rightHandSide){
    // if right hand side is an integer
    if(isInteger(trim(rightHandSide))){
        PT[0].operation = 6;
        strcpy(PT[0].destination,leftHandSide);
        PT[0].operand1 = tokenizeOperand(rightHandSide);
    }
    else{
        PT[0].operation = 7;
        strcpy(PT[0].destination,trim(leftHandSide));
        strcpy(PT[0].source1,trim(rightHandSide));
    }
};

struct SymbolTable* searchInSymbolTable(char* symbol){
    trim(symbol);
    for(int i = 0; i < 20; i++){
        if(strcmp(ST[i].symbol,symbol) == 0) return &ST[i];
    }
    return NULL;
}
