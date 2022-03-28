#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

enum{
    SYMBOL_TK_IDENTIFIER = 500,
    SYMBOL_LIT_INT,
    SYMBOL_LIT_CHAR,
    SYMBOL_LIT_STRING,
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_VECTOR
};

enum{
    DATATYPE_INT = 600,
    DATATYPE_CHAR,
    DATATYPE_FLOAT
};

typedef struct hash_node
{
    int type;
    int datatype;
    char *text;
    struct hash_node * next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
int hashVerifyUndefined(void);

#endif