#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

enum
{
    SYMBOL_TK_IDENTIFIER = 500,
    SYMBOL_LIT_INTEGER,
    SYMBOL_LIT_FLOAT,
    SYMBOL_LIT_CHAR,
    SYMBOL_LIT_STRING,
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_VECTOR
};

enum
{
    DATATYPE_INT = 600,
    DATATYPE_CHAR,
    DATATYPE_FLOAT,
    DATATYPE_STRING
};

typedef struct hash_node
{
    int type;
    int datatype;
    char *text;
    struct hash_node *next;
    struct funcParameters *parameter;
    int quantityOfFuncParameters;
} HASH_NODE;

typedef struct funcParameters
{
    int datatype;
    HASH_NODE *identifier;
    struct funcParameters *next;
} FUNC_PARAMETER;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
int hashCheckUndeclared(void);
void hashInsertFuncParameter(FUNC_PARAMETER *newParameter, HASH_NODE *func);

#endif