// AST - Abstract Syntax Tree

#include "ast.h"

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3) 
{
   AST * newnode = (AST*) calloc(1, sizeof(AST));
   newnode->type = type;
   newnode->symbol = symbol;
   newnode->son[0] = s0;
   newnode->son[1] = s1;
   newnode->son[2] = s2;
   newnode->son[3] = s3;
   return newnode;
}

AST *astCreateSymbol(HASH_NODE *symbol) 
{
   AST * newnode = (AST*) calloc(1, sizeof(AST));
   newnode->type = AST_SYMBOL;
   newnode->symbol = symbol;
   newnode->son[0] = 0;
   newnode->son[1] = 0;
   newnode->son[2] = 0;
   newnode->son[3] = 0;
   return newnode;
}

AST *astPrint(AST *node, int level) 
{
   int i;

   if (node == 0 )
   {
      return 0;
   }
   for ( i = 0; i < level; i++)
   {
      fprintf(stderr, "  |");
   }
   
   fprintf(stderr, "ast (");
   switch (node->type)
   {
      case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
      case AST_DECL: fprintf(stderr, "AST_DECL"); break;
      case AST_DECL_FUNC: fprintf(stderr, "AST_DECL_FUNC"); break;
      case AST_DEC_FUNCTION_INT_PARAM: fprintf(stderr, "AST_DEC_FUNCTION_INT_PARAM"); break;
      case AST_DEC_FUNCTION_FLOAT_PARAM: fprintf(stderr, "AST_DEC_FUNCTION_FLOAT_PARAM"); break;
      case AST_DEC_FUNCTION_CHAR_PARAM: fprintf(stderr, "AST_DEC_FUNCTION_CHAR_PARAM"); break;
      case AST_DEC_FUNCTION_INT: fprintf(stderr, "AST_DEC_FUNCTION_INT"); break;
      case AST_DEC_FUNCTION_FLOAT: fprintf(stderr, "AST_DEC_FUNCTION_FLOAT"); break;
      case AST_DEC_FUNCTION_CHAR: fprintf(stderr, "AST_DEC_FUNCTION_CHAR"); break;
      case AST_PARAMETERS_LIST: fprintf(stderr, "AST_PARAMETERS_LIST"); break;
      case AST_ARG_INT: fprintf(stderr, "AST_ARG_INT"); break;
      case AST_ARG_CHAR: fprintf(stderr, "AST_ARG_CHAR"); break;
      case AST_ARG_FLOAT: fprintf(stderr, "AST_ARG_FLOAT"); break;
      case AST_FLOAT: fprintf(stderr, "AST_FLOAT"); break;
      case AST_INT: fprintf(stderr, "AST_INT"); break;
      case AST_CHAR: fprintf(stderr, "AST_CHAR"); break;
      case AST_ARRAY_FORMAT: fprintf(stderr, "AST_ARRAY_FORMAT_CHAR"); break;
      case AST_ARRAY_VALUES: fprintf(stderr, "AST_ARRAY_VALUES_INT"); break;
      case AST_LCMD: fprintf(stderr, "AST_LCMD"); break;
      case AST_LABEL: fprintf(stderr, "AST_LABEL"); break;
      case AST_ATRIBUTION: fprintf(stderr, "AST_ATRIBUTION"); break;
      case AST_VEC_ATRIBUTION: fprintf(stderr, "AST_VEC_ATRIBUTION"); break;
      case AST_PRINT: fprintf(stderr, "AST_PRINT"); break;
      case AST_WHILE: fprintf(stderr, "AST_WHILE"); break;
      case AST_IF_THEN_ELSE: fprintf(stderr, "AST_IF_THEN_ELSE"); break;
      case AST_IF_THEN: fprintf(stderr, "AST_IF_THEN"); break;
      case AST_GOTO: fprintf(stderr, "AST_GOTO"); break;
      case AST_RETURN: fprintf(stderr, "AST_RETURN"); break;
      case AST_ARRAY_ELEMENT: fprintf(stderr, "AST_ARRAY_ELEMENT"); break;
      case AST_FUNCTION_ARGUMENTS: fprintf(stderr, "AST_FUNCTION_ARGUMENTS"); break;
      case AST_READ: fprintf(stderr, "AST_READ"); break;
      case AST_DIF: fprintf(stderr, "AST_DIF"); break;
      case AST_EQ: fprintf(stderr, "AST_EQ"); break;
      case AST_GE: fprintf(stderr, "AST_GE"); break;
      case AST_LE: fprintf(stderr, "AST_LE"); break;
      case AST_ADD: fprintf(stderr, "AST_ADD"); break; 
      case AST_SUB: fprintf(stderr, "AST_SUB"); break; 
      case AST_MULT: fprintf(stderr, "AST_MULT"); break; 
      case AST_DIV: fprintf(stderr, "AST_DIV"); break;
      case AST_GREATER: fprintf(stderr, "AST_GREATER"); break;
      case AST_LESS: fprintf(stderr, "AST_LESS"); break;
      case AST_LIST_EXPR: fprintf(stderr, "AST_LIST_EXPR"); break;
      case AST_PRINT_VALUES: fprintf(stderr, "AST_PRINT_VALUES"); break;
      case AST_BLOCK: fprintf(stderr, "AST_BLOCK"); break;
      case AST_DEC_INT: fprintf(stderr, "AST_DEC_INT"); break;
      case AST_DEC_CHAR: fprintf(stderr, "AST_DEC_CHAR"); break;
      case AST_DEC_FLOAT: fprintf(stderr, "AST_DEC_FLOAT"); break;
      case AST_ARRAY: fprintf(stderr, "AST_ARRAY"); break;
      case AST_PARENTHESIS: fprintf(stderr, "AST_PARENTHESIS"); break;
       
      default: fprintf(stderr, "AST_UNDEFINED)\n"); break;
   }

   if (node->symbol!=0)
   {
      fprintf(stderr, ", %s)\n", node->symbol->text);
   }
   else
   {
      fprintf(stderr, ", 0)\n");
   }
   
   for (i = 0; i < MAX_SONS; i++)
   {
      astPrint(node->son[i], level+1);
   }
 
}