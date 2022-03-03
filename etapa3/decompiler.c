#include "decompiler.h"

void decompile_AST_TERMINAL(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "%s", node->symbol->text);
}

void decompile_AST_DIV(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " / ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_GREATER(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " > ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_LESSER(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " < ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_OR(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " | ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_AND(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " ^ ");
    decompile(node->son[0], outputFile);
}

void decompile_AST_NOT(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, " ~");
    decompile(node->son[0], outputFile);
}

void decompile_AST_MINUS(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, " -");
    decompile(node->son[0], outputFile);
}

void decompile_AST_DIF(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " != ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_EQ(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " == ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_GE(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " >= ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_LE(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " <= ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_PARENTHESIS(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "(");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, ")");
}

// TK_IDENTIFIER '(' ')'
void decompile_AST_FUNC_CALL(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, "()");
}

// TK_IDENTIFIER '(' expression expressionlist ')'
void decompile_AST_FUNC_PARAMS_CALL(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, "(");
    decompile(node->son[1], outputFile);
    decompile(node->son[2], outputFile);
    fprintf(outputFile, ")");
}

// ',' expression expressionlist   
void decompile_AST_EXPRESSION_LIST(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, ", ");
    decompile(node->son[0], outputFile);
    decompile(node->son[1], outputFile);
}

// KW_WHILE '(' expression ')'
void decompile_AST_WHILE(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "while (");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, ")");
}

// KW_PRINT anything printlist
void decompile_AST_PRINTCMD(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "print ");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " ");
    decompile(node->son[1], outputFile);
}

// KW_RETURN expression
void decompile_AST_RETURN(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "return ");
    decompile(node->son[0], outputFile);
}

void decompile_AST_MULT(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " * ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_SUB(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " - ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_ADD(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " + ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_ATRIBUITION(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " = ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_LCMD(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "  ");
    decompile(node->son[0], outputFile);
}

void decompile_AST_LCMDL(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "  ");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, "\n");
    decompile(node->son[1], outputFile);
}

void decompile_AST_BLOCK(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "{\n");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, "\n}");
}

// ',' assignment assignmentlist
void decompile_AST_FUNC_PARAM_ASSIGN_LIST(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, ", ");
    decompile(node->son[0], outputFile);
    decompile(node->son[1], outputFile);
    
}

// TK_IDENTIFIER '(' assignment assignmentlist ')' '=' vartype block
void decompile_AST_FUNC_PARAMS_DEC(AST *node, FILE* outputFile) 
{
    decompile_AST_SYMBOL(node->son[0], outputFile);
    fprintf(outputFile, "(");
    decompile(node->son[1], outputFile);
    decompile(node->son[2], outputFile);
    fprintf(outputFile, ") = ");
    decompile(node->son[3], outputFile);
    fprintf(outputFile, "\n");
    decompile(node->son[4], outputFile);
}

//TK_IDENTIFIER '(' ')' '=' vartype block  
void decompile_AST_FUNC_VOID_DEC(AST *node, FILE* outputFile) 
{
    decompile_AST_SYMBOL(node->son[0], outputFile);
    fprintf(outputFile, "() = ");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, "\n");
    decompile(node->son[2], outputFile);
}

// TK_IDENTIFIER '[' expression ']' '=' expression
void decompile_AST_ATRIBUITION_VEC(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, "[");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, "] = ");
    decompile(node->son[2], outputFile);
}

void decompile_AST_VEC_INIT_VALUES(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, " ");
    decompile(node->son[0], outputFile);
    decompile(node->son[1], outputFile);
}

// assignment '[' LIT_INTEGER ']' ':' vecvalues
void decompile_AST_VEC_INIT(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, "[");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, "] :");
    decompile(node->son[2], outputFile);
}

void decompile_AST_VEC_DEC(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, "[");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, "]");
}

void decompile_AST_ASSIGNMENT(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " = ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_VARDEC(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " : ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_DECLIST(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, ";\n");
    decompile(node->son[1], outputFile);
}

// TK_IDENTIFIER  '[' expression ']'
void decompile_AST_VECTOR_ACCESS(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, "[");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, "]");
}

// KW_LOOP '(' TK_IDENTIFIER ':' expression ',' expression ',' expression ')' cmd
void decompile_AST_LOOP(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "loop(");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, ":");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, ", ");
    decompile(node->son[2], outputFile);
    fprintf(outputFile, ", ");
    decompile(node->son[3], outputFile);
    fprintf(outputFile, ") \n  ");
    decompile(node->son[4], outputFile);

}

// KW_IF '(' expression ')' KW_THEN cmd
void decompile_AST_IF(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "if(");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, ")\n  then \n  ");
    decompile(node->son[1], outputFile);
}

// KW_IF '(' expression ')' KW_THEN cmd KW_ELSE cmd
void decompile_AST_IF_ELSE(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "if(");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, ")\n  then \n  ");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, " else \n  ");
    decompile(node->son[2], outputFile);
}

// ',' LIT_STRING printlist
void decompile_AST_PRINTLIST(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, ", ");
    decompile(node->son[0], outputFile);
    decompile(node->son[1], outputFile);
}

// KW_READ TK_IDENTIFIER
void decompile_AST_READ(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "read ");
    decompile(node->son[0], outputFile);
}

void decompile(AST* node, FILE *outputFile) 
{
    if (!node)
    {
        return;
    }

    switch (node->type)
    {
        case AST_TERMINAL:
            decompile_AST_TERMINAL(node,outputFile);
            break;
        
            
        default:
            break;
    }
}