#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "hash.h"
#include "ast.h"

#define TRUE 1
#define FALSE 0

int getNumberOfSemanticErrors();
int isValidOperand(AST *node);
int isValidDeclaration(AST *node);
void verifyUndefined();
void verifyDeclarations(AST *node);
void setDataType(AST *node);
void verifyOperands(AST *node);
void printErrorDuringDeclaration(AST *node, char* errorMessage);
void printErrorDuringOperation(AST *node, char* operand, char* operation);


#endif