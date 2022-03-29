#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "hash.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

extern int semanticErrors;
static int returnType;

void checkAndSetDeclarations(AST *node);
void checkUndeclared();
int getSemanticErrors();
void updateDeclarationType(AST *son, AST *parent);
int checkExpr(AST *node);
int checkSymbol(HASH_NODE *node);
int checkIsEscalar(int expr);
void checkCommandsType(AST *node);
int isCompatibleTypes(int identifierType, int exprType);
void checkReturnType(AST *node, int funcType);
void updateParameterList(AST *son, HASH_NODE *func);

#endif