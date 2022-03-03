// AST - Abstract Syntax Tree

#ifndef AST_HEADR
#define AST_HEADR

#include "hash.h"

#define MAX_SONS 4

enum
{
   AST_TERMINAL = 1,  
   
};

typedef struct ast_node
{
   int type;
   HASH_NODE *symbol;
   struct ast_node *son[MAX_SONS];
} AST;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3);
AST *astPrint(AST *node, int level);

// Easier way to create terminal symbols
#define astCreateTerminal(x) astCreate(AST_TERMINAL, x, 0, 0, 0, 0)

#endif