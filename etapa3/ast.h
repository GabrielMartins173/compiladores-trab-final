// AST - Abstract Syntax Tree

#ifndef AST_HEADR
#define AST_HEADR

#include "hash.h"

#define MAX_SONS 4

enum
{
   AST_SYMBOL = 1,
   AST_DECL,
   AST_DECL_FUNC,
   AST_DEC_FUNCTION_INT_PARAM,
   AST_DEC_FUNCTION_FLOAT_PARAM,
   AST_DEC_FUNCTION_CHAR_PARAM,
   AST_DEC_FUNCTION_INT,
   AST_DEC_FUNCTION_FLOAT,
   AST_DEC_FUNCTION_CHAR,
   AST_PARAMETERS_LIST,
   AST_ARG_INT,
   AST_ARG_CHAR,
   AST_ARG_FLOAT,
   AST_FLOAT,
   AST_ARRAY_FORMAT,
   AST_ARRAY_VALUES,
   AST_LCMD,
   AST_LABEL,
   AST_ATRIBUTION,
   AST_VEC_ATRIBUTION,
   AST_PRINT,
   AST_WHILE,
   AST_IF_THEN_ELSE,
   AST_IF_THEN,
   AST_GOTO,
   AST_RETURN,
   AST_ARRAY_ELEMENT,
   AST_FUNCTION_ARGUMENTS,
   AST_READ,
   AST_DIF,
   AST_EQ,
   AST_GE,
   AST_LE,
   AST_ADD,
   AST_SUB,
   AST_MULT,
   AST_DIV,
   AST_GREATER,
   AST_LESS,
   AST_LIST_EXPR,
   AST_PRINT_VALUES,
   AST_BLOCK,
   AST_DEC_INT,
   AST_DEC_CHAR,
   AST_DEC_FLOAT,
   AST_ARRAY,
   AST_LABEL_DECLARATION,
   AST_PARENTHESIS,
   AST_CHAR,
   AST_INT  
   
};

typedef struct ast_node
{
   int type;
   HASH_NODE *symbol;
   struct ast_node *son[MAX_SONS];
} AST;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3);
AST *astPrint(AST *node, int level);

// Alias for creating easilys and compactly an ast_symbol
#define astCreateSymbol(x) astCreate(AST_SYMBOL, x, 0, 0, 0, 0)


#endif // AST_HEADR