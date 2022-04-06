#include "semantic.h"

int numberOfSemanticErrors = 0;
static int returnType = 0;

void checkAndSetDeclarations(AST *node)
{
    int i;

    if (node == 0)
        return;

    if (node->son[0]->son[0]->symbol)
    {
        if ((node->son[0]->son[0]->symbol->type != SYMBOL_TK_IDENTIFIER) && (node->son[0]->son[0]->type == AST_DECL || node->son[0]->son[0]->type == AST_DECL_FUNC || node->son[0]->son[0]->type == AST_DEC_FUNCTION_INT_PARAM || node->son[0]->son[0]->type == AST_DEC_FUNCTION_FLOAT_PARAM || node->son[0]->son[0]->type == AST_DEC_FUNCTION_CHAR_PARAM || node->son[0]->son[0]->type == AST_DEC_FUNCTION_INT || node->son[0]->son[0]->type == AST_DEC_FUNCTION_FLOAT || node->son[0]->son[0]->type == AST_DEC_FUNCTION_CHAR || node->son[0]->son[0]->type == AST_DEC_INT || node->son[0]->son[0]->type == AST_DEC_CHAR || node->son[0]->son[0]->type == AST_DEC_FLOAT || node->son[0]->son[0]->type == AST_ARRAY_FORMAT || node->son[0]->son[0]->type == AST_ARRAY || node->son[0]->son[0]->type == AST_ARRAY_VALUES))
        {
            fprintf(stderr, "Semantic Error Found: Variable %s is redeclared \n", node->son[0]->son[0]->symbol->text);
            numberOfSemanticErrors++;
        }

        switch (node->son[0]->son[0]->type)
        {
        case AST_DECL:
        case AST_PARAMETERS_LIST:
        case AST_ARG_INT:
        case AST_ARG_FLOAT:
        case AST_ARG_CHAR:
        case AST_DEC_INT:
        case AST_DEC_CHAR:
        case AST_DEC_FLOAT:
        case AST_LIST_EXPR:
        case AST_PRINT_VALUES:
            node->son[0]->son[0]->symbol->type = SYMBOL_VARIABLE;
            updateDeclarationType(node->son[0]->son[0]->son[0], node);
            break;

        case AST_DECL_FUNC:
        case AST_DEC_FUNCTION_INT_PARAM:
        case AST_DEC_FUNCTION_FLOAT_PARAM:
        case AST_DEC_FUNCTION_CHAR_PARAM:
        case AST_DEC_FUNCTION_INT:
        case AST_DEC_FUNCTION_FLOAT:
        case AST_DEC_FUNCTION_CHAR:
        {
            node->son[0]->son[0]->symbol->type = SYMBOL_FUNCTION;
            updateDeclarationType(node->son[0]->son[0]->son[1], node);
            updateParameterList(node->son[0]->son[0]->son[0], node->symbol);

            returnType = 0;
            checkReturnType(node->son[0]->son[0]->son[2], node->son[0]->son[0]->symbol->datatype);

            if (returnType != node->son[0]->son[0]->symbol->datatype && returnType != 0)
            {
                fprintf(stderr, "Semantic Error Found: Function %s with type DATA_TYPE_%i has wrong return with type DATA_TYPE_%i \n", node->son[0]->son[0]->symbol->text, node->son[0]->son[0]->symbol->datatype, returnType);
                numberOfSemanticErrors++;
            }

            break;
        }

        case AST_ARRAY_FORMAT:
        case AST_ARRAY:
        case AST_ARRAY_VALUES:
            node->son[0]->son[0]->symbol->type = SYMBOL_VECTOR;
            updateDeclarationType(node->son[0]->son[0]->son[0], node);
            break;

        case AST_SYMBOL:
        {
            switch (node->son[0]->son[0]->symbol->type)
            {
            case SYMBOL_LIT_CHAR:
                node->son[0]->son[0]->symbol->datatype = DATATYPE_CHAR;
                break;
            case SYMBOL_LIT_FLOAT:
                node->son[0]->son[0]->symbol->datatype = DATATYPE_FLOAT;
                break;
            case SYMBOL_LIT_INTEGER:
                node->son[0]->son[0]->symbol->datatype = DATATYPE_INT;
                break;
            case SYMBOL_LIT_STRING:
                node->son[0]->son[0]->symbol->datatype = DATATYPE_STRING;
                break;
            }
        }
        }
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        checkAndSetDeclarations(node->son[0]->son[0]->son[i]);
    }
}

void checkCommandsType(AST *node)
{

    int i;

    if (node == 0)
        return;

    switch (node->son[0]->son[0]->type)
    {
    case AST_ATRIBUTION:
    {
        int identifierType = checkSymbol(node->son[0]->son[0]->symbol);
        int exprType = checkExpr(node->son[0]->son[0]->son[0]);

        if (!(checkIsEscalar(identifierType) && checkIsEscalar(exprType)))
        {
            fprintf(stderr, "Semantic Error Found: Variable %s of type DATA_TYPE_%i has wrong assigned type of %i \n", node->son[0]->son[0]->symbol->text, identifierType, exprType);
            numberOfSemanticErrors++;
        }
        else if (node->son[0]->son[0]->symbol->type != SYMBOL_VARIABLE)
        {
            fprintf(stderr, "Semantic Error Found: Identifier %s of type DATA_TYPE_%i is not a variable \n", node->son[0]->son[0]->symbol->text, identifierType);
            numberOfSemanticErrors++;
        }
        break;
    }

    case AST_VEC_ATRIBUTION:
    {
        int identifierType = checkSymbol(node->son[0]->son[0]->symbol);
        int indexType = checkExpr(node->son[0]->son[0]->son[0]);
        int exprType = checkExpr(node->son[0]->son[0]->son[1]);

        if (indexType == DATATYPE_FLOAT || (areNotCompatibleTypes(identifierType, exprType)))
        {
            fprintf(stderr, "Semantic Error Found: vector %s of type DATA_TYPE_%i with index DATA_TYPE_%i has assigned type of %i \n", node->son[0]->son[0]->symbol->text, identifierType, indexType, exprType);
            numberOfSemanticErrors++;
        }
        else if (node->son[0]->son[0]->symbol->type != SYMBOL_VECTOR)
        {
            fprintf(stderr, "Semantic Error Found: Identifier %s of type DATA_TYPE_%i is not a vector \n", node->son[0]->son[0]->symbol->text, identifierType);
            numberOfSemanticErrors++;
        }
        break;
    }

    case AST_IF_THEN:
    case AST_IF_THEN_ELSE:
    case AST_WHILE:
    {
        int condition = checkExpr(node->son[0]->son[0]->son[0]);

        if (!checkIsEscalar(condition))
        {
            switch (node->son[0]->son[0]->type)
            {
            case AST_IF_THEN_ELSE:
            case AST_IF_THEN:
                fprintf(stderr, "Semantic Error Found if conditional has wrong type \n");
                break;

            case AST_WHILE:
                fprintf(stderr, "Semantic Error Found while conditional has wrong type \n");
                break;
            }

            fprintf(stderr, "Semantic Error Found if conditional has wrong type \n");
            numberOfSemanticErrors++;
        }
        break;
    }

    default:
        for (i = 0; i < MAX_SONS; i++)
            checkCommandsType(node->son[0]->son[0]->son[i]);
        break;
    }
}

int checkExpr(AST *node)
{
    int i;

    if (node == 0)
    {
        return -1;
    }

    switch (node->type)
    {
    case AST_ADD:
    case AST_SUB:
    case AST_DIV:
    case AST_MULT:
    case AST_GREATER:
    case AST_LESS:
    case AST_LE:
    case AST_GE:
    case AST_EQ:
    case AST_DIF:
    {
        int leftOperand = checkExpr(node->son[0]);
        int rightOperand = checkExpr(node->son[1]);

        switch (node->type)
        {
        case AST_GREATER:
        case AST_LESS:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_DIF:
        {
            if (checkIsEscalar(leftOperand) && checkIsEscalar(rightOperand))
            {
                return DATATYPE_INT;
            }
            else
            {
                fprintf(stderr, "Semantic Error Found: Invalid operands for comparable operation AST_%i. It is < DATA_TYPE_%i OPERATION DATA_TYPE_%i > \n", node->type, leftOperand, rightOperand);
                numberOfSemanticErrors++;
            }
            break;
        }

        default:
        {
            if (checkIsEscalar(leftOperand) && checkIsEscalar(rightOperand))
            {
                if (leftOperand == DATATYPE_INT || rightOperand == DATATYPE_INT)
                    return DATATYPE_INT;
                return DATATYPE_FLOAT;
            }
            else
            {
                fprintf(stderr, "Semantic Error Found: Invalid operands for arithmetic operation AST_%i. It is < DATA_TYPE_%i OPERATION DATA_TYPE_%i > \n", node->type, leftOperand, rightOperand);
                numberOfSemanticErrors++;
            }
        }
        }
        break;
    }

    case AST_SYMBOL:

        if (node->symbol->datatype != SYMBOL_VARIABLE && node->son[0])
        {
            fprintf(stderr, "Semantic Error Found: Invalid vector %s being accessed as a variable. \n", node->symbol->text);
            numberOfSemanticErrors++;
        }
        else if (node->symbol->type == SYMBOL_FUNCTION)
        {
            fprintf(stderr, "Semantic Error Found: Variable %s is not a function. \n", node->symbol->text);
            numberOfSemanticErrors++;
        }
        else
            return checkSymbol(node->symbol);
        break;

    case AST_ARRAY_ELEMENT:
    {
        int indexType = checkExpr(node->son[0]);

        if (node->symbol->type != SYMBOL_VECTOR)
        {
            fprintf(stderr, "Semantic Error Found: Variable %s IS NOT a vector. \n", node->symbol->text);
            numberOfSemanticErrors++;
        }
        else if (!checkIsEscalar(indexType))
        {
            fprintf(stderr, "Semantic Error Found: Invalid vector index DATA_TYPE_%i. \n", indexType);
            numberOfSemanticErrors++;
        }
        else if (checkIsEscalar(indexType) && indexType != DATATYPE_FLOAT)
            return checkSymbol(node->symbol);
        break;
    }

    case AST_FUNCTION_ARGUMENTS:
    {
        if (node->symbol->type != SYMBOL_FUNCTION)
        {
            fprintf(stderr, "Semantic Error Found: Variable %s DATA_TYPE_%i is not a function \n", node->symbol->text, node->symbol->datatype);
            numberOfSemanticErrors++;
            break;
        }

        AST *currentNode = node->son[0];
        FUNC_PARAMETER *currentParameter = node->symbol->parameter;

        for (int i = 1; i < node->symbol->quantityOfFuncParameters; i++)
        {
            int parameterType = checkExpr(currentNode->son[0]);

            if (parameterType != currentParameter->datatype)
            {
                fprintf(stderr, "Semantic Error Found: Parameter %s should be of DATA_TYPE_%i. Currently it is DATA_TYPE_%i \n", currentParameter->identifier->text, currentParameter->datatype, parameterType);
                numberOfSemanticErrors++;
            }

            currentNode = currentNode->son[1];

            if (!currentNode)
            {
                fprintf(stderr, "Semantic Error Found: Function call %s has less arguments than declared \n", node->symbol->text);
                numberOfSemanticErrors++;
            }

            currentParameter = currentParameter->next;
        }

        if (currentNode && currentNode->son[1])
        {
            fprintf(stderr, "Semantic Error Found: Function call %s has more arguments than declared \n", node->symbol->text);
            numberOfSemanticErrors++;
        }

        return checkSymbol(node->symbol);
    }

    case AST_PARENTHESIS:
        return checkExpr(node->son[0]);

    
    default:
        for (i = 0; i < MAX_SONS; i++)
        {
            checkExpr(node->son[i]);
        }
        break;
    }

    return -1;
}

int areNotCompatibleTypes(int identifierType, int exprType)
{
    return !(checkIsEscalar(identifierType) && checkIsEscalar(exprType));
}

void updateParameterList(AST *node, HASH_NODE *func)
{
    int i;

    if (node == 0)
    {
        return;
    }

    switch (node->type)
    {
    case AST_PARAMETERS_LIST:
    case AST_ARG_INT:
    case AST_ARG_FLOAT:
    case AST_ARG_CHAR:
    {
        if (hashFind(node->symbol->text) && node->symbol->type == SYMBOL_VARIABLE)
        {
            fprintf(stderr, "Semantic Error Found: Func Parameter %s is redeclared with AST_TYPE_%i\n", node->symbol->text, node->symbol->type);
            numberOfSemanticErrors++;
        }

        FUNC_PARAMETER *newParameter = (FUNC_PARAMETER *)calloc(1, sizeof(FUNC_PARAMETER));
        newParameter->identifier = node->symbol;

        switch (node->son[0]->type)
        {
        case AST_DEC_CHAR:
            node->symbol->datatype = newParameter->datatype = DATATYPE_CHAR;
            break;
        case AST_DEC_FLOAT:
            node->symbol->datatype = newParameter->datatype = DATATYPE_FLOAT;
            break;
        case AST_DEC_INT:
            node->symbol->datatype = newParameter->datatype = DATATYPE_INT;
            break;
        }

        hashInsertFuncParameter(newParameter, func);
    }
    }
    for (i = 0; i < MAX_SONS; i++)
    {
        updateParameterList(node->son[i], func);
    }
}

void updateDeclarationType(AST *son, AST *parent)
{
    if (son)
    {
        switch (son->type)
        {
        case AST_DEC_CHAR:
            parent->symbol->datatype = DATATYPE_CHAR;
            break;

        case AST_DEC_FLOAT:
            parent->symbol->datatype = DATATYPE_FLOAT;
            break;

        case AST_DEC_INT:
            parent->symbol->datatype = DATATYPE_INT;
            break;
        }
    }
}

void checkReturnType(AST *node, int funcType)
{
    int i;

    if (node == 0)
    {
        return;
    }

    switch (node->type)
    {

    case AST_RETURN:
    {
        int internalReturnType = checkExpr(node->son[0]);
        if (checkIsEscalar(internalReturnType) != checkIsEscalar(funcType))
        {
            returnType = internalReturnType;
        }
        break;
    }
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        checkReturnType(node->son[i], funcType);
    }
}

int checkIsEscalar(int expr)
{
    return expr == DATATYPE_INT || expr == DATATYPE_FLOAT || expr == DATATYPE_CHAR;
}

int checkSymbol(HASH_NODE *node)
{
    return node->datatype;
}

void checkUndeclared()
{
    numberOfSemanticErrors += hashCheckUndeclared();
}

int getSemanticErrors()
{
    return numberOfSemanticErrors;
}