/*Autor Gabriel Martins dos Santos*/

%{
#include "tokens.h"
#include "main.c"
int lineNumber = 1;
int running = 1;
%}

%x COMMENT

%%
int                 {return KW_INT;}
[0-9]+              {return LIT_INTEGER;}
[-;{}+:]            {return yytext[0];}
"/n"                {lineNumber++;}
[ \t]
"//".*
"/*"                {BEGIN(COMMENT);}
.                   {return TOKEN_ERROR;}
<COMMENT>"*/"       {BEGIN(INITIAL);}
<COMMENT>"\n"       {lineNumber++;}
<COMMENT>.
%%


int yywrap(){
    running = 0;
    return 1;
}

int isRunning() {
    return running;
}