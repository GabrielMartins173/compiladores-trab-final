#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HASH_NODE *Table[HASH_SIZE];

void hashInit(void)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++)
        Table[i] = 0;
}

int hashAddress(char *text)
{
    int address = 1;
    int i;
    for (i = 0; i < strlen(text); i++)
        address = (address * text[i]) % HASH_SIZE + 1;
    return address - 1;
}

HASH_NODE *hashFind(char *text)
{
    HASH_NODE *node;
    int address = hashAddress(text);
    for (node = Table[address]; node; node = node->next)
        if (strcmp(node->text, text) == 0)
            return node;
    return 0;
}

HASH_NODE *hashInsert(char *text, int type)
{
    HASH_NODE *newnode;
    int address = hashAddress(text);

    if ((newnode = hashFind(text)) != 0)
        return newnode;

    newnode = (HASH_NODE *)calloc(1, sizeof(HASH_NODE));
    newnode->type = type;
    newnode->text = (char *)calloc(strlen(text) + 1, sizeof(char));
    newnode->quantityOfFuncParameters = 0;
    strcpy(newnode->text, text);
    newnode->next = Table[address];
    Table[address] = newnode;
    return newnode;
}

void hashPrint(void)
{
    int i;
    HASH_NODE *node;
    FUNC_PARAMETER *parameter;

    for (i = 0; i < HASH_SIZE; i++)
        for (node = Table[i]; node; node = node->next)
        {
            fprintf(stderr, "\nTable[%d] has %s with SYMBOL_%i and DATA_TYPE_%i with %i parameters", i, node->text, node->type, node->datatype, node->quantityOfFuncParameters);
        }

    for (parameter = node->parameter; parameter; parameter = parameter->next)
        fprintf(stderr, "\n     %s = DATA_TYPE_%i", parameter->identifier->text, parameter->datatype);
}

int hashCheckUndeclared(void)
{
    int undeclared = 0;
    HASH_NODE *node;

    for (int i = 0; i < HASH_SIZE; i++)
    {
        for (node = Table[i]; node; node = node->next)
        {
            if (node->type == SYMBOL_TK_IDENTIFIER)
            {
                printf("SEMANTIC ERROR!! The following identifier %s is undeclared\n", node->text);
                undeclared++;
            }
        }
    }
    return undeclared;
}

void hashInsertFuncParameter(FUNC_PARAMETER *newParameter, HASH_NODE *func)
{
    if (!func->parameter)
    {
        func->parameter = newParameter;
    }
    else
    {
        FUNC_PARAMETER *currentParameter = func->parameter;
        while (currentParameter->next)
        {
            currentParameter = currentParameter->next;
        }
        currentParameter->next = newParameter;
    }

    func->quantityOfFuncParameters++;
    fprintf(stderr, "\n");
}