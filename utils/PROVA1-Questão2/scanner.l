/* Autor Gabriel Martins dos Santos - 00275617 */

%{
#include "tokens.h"
int A_Scope = 1;
int B_Scope = 0;
int running = 1;
int lineNumber = 1;
int numberOfErrors = 0;
%}

%%

[0-9]+                       {return LIT_LING_A;}
[_]*[a-zA-Z]+[a-zA-Z0-9]*    {return IDENTIFIER_LING_A;}

"#{"                         {A_Scope = 0; B_Scope = 1; return OPEN_SCOPE_LING_B;}
"#}"                         {A_Scope = 1; B_Scope = 0; return CLOSE_SCOPE_LING_B;}

[0x]+[A-Fa-f0-9]+            {return LIT_LING_B;}
[_]*[a-zA-Z]+[a-zA-Z0-9 ]*   {return IDENTIFIER_LING_B;}

"\n"                         {lineNumber++;}
[ \t]

.                            {numberOfErrors++; return TOKEN_ERROR;}

%%

#include "main.c"
#include "tokens.h"

int yywrap(){
    running = 0;
    return 1;
}

int isRunning() {
    return running;
}

int isA_Scope(){
    return A_Scope;
}

int isB_Scope(){
    return B_Scope;
}

int getLineNumber(){
    return lineNumber;
}

int getNumberOfErrors(){
    return numberOfErrors;
}