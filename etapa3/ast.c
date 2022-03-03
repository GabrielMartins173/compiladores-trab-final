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

AST *astPrint(AST *node, int level) 
{
   int i;

   if (node ==0 )
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
      case AST_TERMINAL: fprintf(stderr, "AST_TERMINAL"); break;
   
      
      default: fprintf(stderr, "AST_UNDEFINED"); break;
   }

   if (node->symbol!=0)
   {
      fprintf(stderr, ", %s\n", node->symbol->text);
   }
   else
   {
      fprintf(stderr, ", 0\n");
   }

   for (i = 0; i < MAX_SONS; i++)
   {
      astPrint(node->son[i], level+1);
   }
}