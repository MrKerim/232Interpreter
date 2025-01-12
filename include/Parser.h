#ifndef PARSER_H
#define PARSER_H

void Parser(char *input);

int isInteger(const char *str);

char* trim(char* str);

int getConditionCode(char* input);

char** seperateIFandExpression(char *input);

void handleIFStatementParsing(char* ifClause);

struct Ary tokenizeOperand(char* operand);

void handleExpressionParsing(char* expression);

void handleArithmeticOperationParsing(char* expression);

void handleExchangeFunctionParsing(char* expression);

void handlePrintFunctionParsing(char* expression);

void handleSumAvarageDiagonalParsing(char* rightHandSide, char* leftHandSide);

void handleInitializeArrayParsing(char* leftHandSide, char* rightHandSide);

void handleInitASingleVariable(char* leftHandSide, char* rightHandSide);

void handleSetOrCopyFunctionParsing(char* leftHandSide, char* rightHandSide);

struct SymbolTable* searchInSymbolTable(char* symbol);

#endif