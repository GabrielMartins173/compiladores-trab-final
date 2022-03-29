#include "semantic.h"

int numberOfSemanticErrors = 0;
static int returnType = 0;

void checkAndSetDeclarations(AST *node)
{
}

void checkCommandsType(AST *node)
{

    int i;

    if (node == 0)
        return;

    switch (node->type)
    {
    case AST_ATRIBUTION:
    {
        int identifierType = checkSymbol(node->symbol);
        int exprType = checkExpr(node->son[0]);

        if (!(checkIsEscalar(identifierType) && checkIsEscalar(exprType)))
        {
            fprintf(stderr, "Semantic Error Found: Variable %s of type DATA_TYPE_%i has wrong assigned type of %i \n", node->symbol->text, identifierType, exprType);
            numberOfSemanticErrors++;
        }
        else if (node->symbol->type != SYMBOL_VARIABLE)
        {
            fprintf(stderr, "Semantic Error Found: Identifier %s of type DATA_TYPE_%i is not a variable \n", node->symbol->text, identifierType);
            numberOfSemanticErrors++;
        }
        break;
    }

    case AST_VEC_ATRIBUTION:
    {
        int identifierType = checkSymbol(node->symbol);
        int indexType = checkExpr(node->son[0]);
        int exprType = checkExpr(node->son[1]);

        if (indexType == DATATYPE_FLOAT || (isCompatibleTypes(identifierType, exprType)))
        {
            fprintf(stderr, "Semantic Error Found: vector %s of type DATA_TYPE_%i with index DATA_TYPE_%i has assigned type of %i \n", node->symbol->text, identifierType, indexType, exprType);
            numberOfSemanticErrors++;
        }
        else if (node->symbol->type != SYMBOL_VECTOR)
        {
            fprintf(stderr, "Semantic Error Found: Identifier %s of type DATA_TYPE_%i is not a vector \n", node->symbol->text, identifierType);
            numberOfSemanticErrors++;
        }
        break;
    }

    case AST_IF_THEN:
    case AST_IF_THEN_ELSE:
    case AST_WHILE:
    {
        int condition = checkExpr(node->son[0]);

        if (!checkIsEscalar(condition))
        {
            switch (node->type)
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
            checkCommandsType(node->son[i]);
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

    case AST_READ:
    default:
        for (i = 0; i < MAX_SONS; i++)
        {
            checkExpr(node->son[i]);
        }
        break;
    }

    return -1;
}

int isCompatibleTypes(int identifierType, int exprType)
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
