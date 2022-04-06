#include "decompiler.h"

void decompile_AST_SYMBOL(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "%s", node->symbol->text);
}

void decompile_AST_DECL(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, "; \n");
    decompile(node->son[1], outputFile);
}

void decompile_AST_DECL_FUNC(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " \n");
    decompile(node->son[1], outputFile);
}
 
void decompile_AST_DEC_FUNCTION_INT_PARAM(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "int ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "(");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, ")");
    decompile(node->son[2], outputFile);
}  

void decompile_AST_DEC_FUNCTION_FLOAT_PARAM(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "float ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "(");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, ")");
    decompile(node->son[2], outputFile);
}  

void decompile_AST_DEC_FUNCTION_CHAR_PARAM(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "char ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "(");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, ")");
    decompile(node->son[2], outputFile);
}

void decompile_AST_DEC_FUNCTION_INT(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "int ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "()");
    decompile(node->son[1], outputFile);
}

void decompile_AST_DEC_FUNCTION_FLOAT(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "float ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "()");
    decompile(node->son[1], outputFile);
}

void decompile_AST_DEC_FUNCTION_CHAR(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "char ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "()");
    decompile(node->son[1], outputFile);
}

void decompile_AST_PARAMETERS_LIST(AST *node, FILE* outputFile)
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, ",");
    decompile(node->son[1], outputFile);
}

void decompile_AST_ARG_INT(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "int ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
}

void decompile_AST_ARG_CHAR(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "char ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
}

void decompile_AST_ARG_FLOAT(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "float ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
} 

void decompile_AST_DEC_INT(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "int ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    decompile(node->son[1], outputFile);
}

void decompile_AST_DEC_CHAR(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "char ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    decompile(node->son[1], outputFile);
}

void decompile_AST_DEC_FLOAT(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "float ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    decompile(node->son[1], outputFile);
}

void decompile_AST_INT(AST *node, FILE* outputFile)
{
    fprintf(outputFile, ":");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
}

void decompile_AST_CHAR(AST *node, FILE* outputFile)
{
    fprintf(outputFile, ":");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
}

void decompile_AST_FLOAT(AST *node, FILE* outputFile)
{
    fprintf(outputFile, ":");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "/");
    fprintf(outputFile, "%s", node->son[1]->symbol->text);
} 

void decompile_AST_ARRAY_FORMAT(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "[");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "]:");
    fprintf(outputFile, "%s", node->son[1]->symbol->text);
    decompile(node->son[2], outputFile);
}

void decompile_AST_ARRAY(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "[");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "]");
}

void decompile_AST_ARRAY_VALUES(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    decompile(node->son[1], outputFile);
}

void decompile_AST_LCMD(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, "; \n");
    decompile(node->son[1], outputFile);
}

void decompile_AST_LABEL(AST *node, FILE* outputFile)
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, ": \n");
    decompile(node->son[1], outputFile);
}

void decompile_AST_ATRIBUTION(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, " = ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_VEC_ATRIBUTION(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "[");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, "] = ");
    decompile(node->son[2], outputFile);
}

void decompile_AST_PRINT(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "print ");
    decompile(node->son[0], outputFile);
}

void decompile_AST_WHILE(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "while ");
    decompile(node->son[0], outputFile);
    decompile(node->son[1], outputFile);
}

void decompile_AST_IF_THEN_ELSE(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "if ");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " \nthen \n ");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, "else \n ");
    decompile(node->son[2], outputFile);
}

void decompile_AST_IF_THEN(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "if ");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " \nthen \n ");
    decompile(node->son[1], outputFile);
} 

void decompile_AST_GOTO(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "goto ");
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
}

void decompile_AST_RETURN(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "return ");
    decompile(node->son[0], outputFile);
}

void decompile_AST_BLOCK(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "{\n");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, "\n}");
}


void decompile_AST_ARRAY_ELEMENT(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "[");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, "]");
}

void decompile_AST_FUNCTION_ARGUMENTS(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "%s", node->son[0]->symbol->text);
    fprintf(outputFile, "(");
    decompile(node->son[1], outputFile);
    fprintf(outputFile, ")");
}

void decompile_AST_READ(AST *node, FILE* outputFile) 
{
    fprintf(outputFile, "read ");
}

void decompile_AST_PARENTHESIS(AST *node, FILE* outputFile)
{
    fprintf(outputFile, "(");
    decompile(node->son[0], outputFile);
    fprintf(outputFile, ")");
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

void decompile_AST_ADD(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " + ");
    decompile(node->son[1], outputFile);
} 

void decompile_AST_SUB(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " - ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_MULT(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " * ");
    decompile(node->son[1], outputFile);
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

void decompile_AST_LESS(AST *node, FILE* outputFile) 
{
    decompile(node->son[0], outputFile);
    fprintf(outputFile, " < ");
    decompile(node->son[1], outputFile);
}

void decompile_AST_LIST_EXPR(AST *node, FILE* outputFile)
{
    if(node->son[1] != 0){
        decompile(node->son[0], outputFile);  
        fprintf(outputFile, " , ");
        decompile(node->son[1], outputFile);
    }
    else{
        decompile(node->son[0], outputFile); 
    }
}

void decompile_AST_PRINT_VALUES(AST *node, FILE* outputFile)
{
    if(node->son[1] != 0){
        decompile(node->son[0], outputFile);  
        fprintf(outputFile, " , ");
        decompile(node->son[1], outputFile);
    }
    else{
        decompile(node->son[0], outputFile); 
    }
}

//Decompile functions END

void decompile(AST* node, FILE *outputFile) 
{
    if (!node)
    {
        return;
    }

    switch (node->type)
    {
        case AST_SYMBOL:
            decompile_AST_SYMBOL(node,outputFile);
            break;

        case AST_DECL:  
            decompile_AST_DECL(node,outputFile);
            break;

        case AST_DECL_FUNC:  
            decompile_AST_DECL_FUNC(node,outputFile);
            break;

        case AST_DEC_FUNCTION_INT_PARAM: 
            decompile_AST_DEC_FUNCTION_INT_PARAM(node,outputFile);
            break;

        case AST_DEC_FUNCTION_FLOAT_PARAM:  
            decompile_AST_DEC_FUNCTION_FLOAT_PARAM(node,outputFile);
            break;

        case AST_DEC_FUNCTION_CHAR_PARAM:  
            decompile_AST_DEC_FUNCTION_CHAR_PARAM(node,outputFile);
            break;

        case AST_DEC_FUNCTION_INT: 
            decompile_AST_DEC_FUNCTION_INT(node,outputFile);
            break;

        case AST_DEC_FUNCTION_CHAR: 
            decompile_AST_DEC_FUNCTION_CHAR(node,outputFile);
            break;

        case AST_DEC_FUNCTION_FLOAT: 
            decompile_AST_DEC_FUNCTION_FLOAT(node,outputFile);
            break;

        case AST_PARAMETERS_LIST: 
            decompile_AST_PARAMETERS_LIST(node,outputFile);
            break;

        case AST_ARG_INT: 
            decompile_AST_ARG_INT(node,outputFile);
            break;

        case AST_ARG_CHAR: 
            decompile_AST_ARG_CHAR(node,outputFile);
            break;

        case AST_ARG_FLOAT: 
            decompile_AST_ARG_FLOAT(node,outputFile);
            break;

        case AST_FLOAT: 
            decompile_AST_FLOAT(node,outputFile);
            break;

        case AST_ARRAY_FORMAT: 
            decompile_AST_ARRAY_FORMAT(node,outputFile);
            break;

        case AST_ARRAY_VALUES: 
            decompile_AST_ARRAY_VALUES(node,outputFile);
            break;

        case AST_LCMD: 
            decompile_AST_LCMD(node,outputFile);
            break;

        case AST_BLOCK: 
            decompile_AST_BLOCK(node,outputFile);
            break;

        case AST_LABEL: 
            decompile_AST_LABEL(node,outputFile);
            break;

        case AST_ATRIBUTION:
            decompile_AST_ATRIBUTION(node,outputFile);
            break;

        case AST_VEC_ATRIBUTION: 
            decompile_AST_VEC_ATRIBUTION(node,outputFile);
            break;

        case AST_PRINT: 
            decompile_AST_PRINT(node,outputFile);
            break;

        case AST_WHILE:
            decompile_AST_WHILE(node,outputFile);
            break;

        case AST_IF_THEN_ELSE: 
            decompile_AST_IF_THEN_ELSE(node,outputFile);
            break;

        case AST_IF_THEN: 
            decompile_AST_IF_THEN(node,outputFile);
            break;

        case AST_GOTO: 
            decompile_AST_GOTO(node,outputFile);
            break;

        case AST_RETURN: 
            decompile_AST_RETURN(node,outputFile);
            break;

        case AST_ARRAY_ELEMENT:  
            decompile_AST_ARRAY_ELEMENT(node,outputFile);
            break;

        case AST_FUNCTION_ARGUMENTS: 
            decompile_AST_FUNCTION_ARGUMENTS(node,outputFile);
            break;

        case AST_READ: 
            decompile_AST_READ(node,outputFile);
            break;

        case AST_DIF: 
            decompile_AST_DIF(node,outputFile);
            break;

        case AST_EQ: 
            decompile_AST_EQ(node,outputFile);
            break;

        case AST_GE: 
            decompile_AST_GE(node,outputFile);
            break;

        case AST_LE: 
            decompile_AST_LE(node,outputFile);
            break;

        case AST_ADD: 
            decompile_AST_ADD(node,outputFile); 
            break; 

        case AST_SUB: 
            decompile_AST_SUB(node,outputFile);
            break;

        case AST_MULT: 
            decompile_AST_MULT(node,outputFile);
            break;

        case AST_DIV: 
            decompile_AST_DIV(node,outputFile);
            break;

        case AST_GREATER: 
            decompile_AST_GREATER(node,outputFile);
            break;

        case AST_LESS: 
            decompile_AST_LESS(node,outputFile);
            break;

        case AST_LIST_EXPR: 
            decompile_AST_LIST_EXPR(node,outputFile);
            break;

        case AST_PRINT_VALUES: 
            decompile_AST_PRINT_VALUES(node,outputFile);
            break;

        case AST_DEC_INT: 
            decompile_AST_DEC_INT(node,outputFile);
            break;

        case AST_DEC_CHAR: 
            decompile_AST_DEC_CHAR(node,outputFile);
            break;

        case AST_DEC_FLOAT: 
            decompile_AST_DEC_FLOAT(node,outputFile);
            break;

        case AST_ARRAY: 
            decompile_AST_ARRAY(node,outputFile);
            break;

        case AST_PARENTHESIS: 
            decompile_AST_PARENTHESIS(node,outputFile);
            break;

        case AST_INT: 
            decompile_AST_INT(node,outputFile);
            break;

        case AST_CHAR: 
            decompile_AST_CHAR(node,outputFile);
            break;

        default:
            break;
    }
}