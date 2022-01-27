/* Autor Gabriel Martins dos Santos - 00275617 */

%{
#include "tokens.h"
#include "hash.h"
int lineNumber = 1;
int numberOfErrors = 0;
int running = 1;
%}

%x COMMENT

%%
char                    {return KW_CHAR;}
int                     {return KW_INT;}
float                   {return KW_FLOAT;}
if                      {return KW_IF;}
then                    {return KW_THEN;}
else                    {return KW_ELSE;}
while                   {return KW_WHILE;}
goto                    {return KW_GOTO;}
read                    {return KW_READ;}
print                   {return KW_PRINT;}
return                  {return KW_RETURN;}

"<="                    {return OPERATOR_LE;}
">="                    {return OPERATOR_GE;}
"=="                    {return OPERATOR_EQ;}
"!="                    {return OPERATOR_DIF;}

[0-9]+                  {hashInsert(yytext, LIT_INTEGER); return LIT_INTEGER;}
[a-z|_|-]*              {return TK_IDENTIFIER;}
'.'                     {hashInsert(yytext, LIT_CHAR); return LIT_CHAR;}
\".*\"                  {hashInsert(yytext, LIT_STRING); return LIT_STRING;}

[-+*/<>=,;:(){}\[\]]    {return yytext[0];}
"\n"                    {lineNumber++;}

[ \t]
"\\\\".*
"\\*"                   {BEGIN(COMMENT);}
.                       {numberOfErrors++; return TOKEN_ERROR;}
<COMMENT>"*\\"          {BEGIN(INITIAL);}
<COMMENT>"\n"           {lineNumber++;}
<COMMENT>.
%%

#include "tokens.h"
#include "hash.c"
#include "main.c"

int yywrap(){
    running = 0;
    return 1;
}

int isRunning() {
    return running;
}

int getLineNumber(){
    return lineNumber;
}

int getNumberOfErrors(){
    return numberOfErrors;
}

void printHashTable(){
    hashPrint();
}

void initMe(){
    hashInit();
}