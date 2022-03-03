%{

#include "ast.h"
int yyerror();
extern int getLineNumber();
AST* Root = NULL;

%}

%union
{
    HASH_NODE *symbol;
    AST *ast;
}

%token KW_CHAR           
%token KW_INT            
%token KW_FLOAT          

%token KW_IF             
%token KW_THEN           
%token KW_ELSE           
%token KW_WHILE          
%token KW_GOTO           
%token KW_READ           
%token KW_PRINT          
%token KW_RETURN         

%token OPERATOR_LE       
%token OPERATOR_GE       
%token OPERATOR_EQ       
%token OPERATOR_DIF      

%token<symbol> TK_IDENTIFIER     

%token<symbol> LIT_INTEGER       
%token<symbol> LIT_CHAR          
%token<symbol> LIT_STRING    

%token TOKEN_ERROR

%type<ast> program
%type<ast> decl
%type<ast> closeDecl
%type<ast> closeFunc
%type<ast> decFunction
%type<ast> parametersList
%type<ast> parameter
%type<ast> dec
%type<ast> decIntChar
%type<ast> decFloat
%type<ast> arrayFormat
%type<ast> arrayValues
%type<ast> lcmd
%type<ast> label
%type<ast> cmd
%type<ast> expr
%type<ast> listExpr
%type<ast> printValues
%type<ast> printParameter

%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF '<' '>'
%left '+' '-'
%left '*' '/'

%%

program: decl {$$ = $1; Root = $$; /*astPrint($1, 0);*/}
    ;

decl: dec closeDecl             {$$ = astCreate(AST_DECL, 0, $1, $2, 0, 0); /*astPrint($1, 0);*/}
    | decFunction closeFunc     {$$ = astCreate(AST_DECL, 0, $1, $2, 0, 0); /*astPrint($1, 0);*/}
    |                           {$$ = 0; }
    ;
    
closeDecl: ';' decl             {$$ = $2;}
    ;

closeFunc: decl                 {$$ = $1;}
    ;

decFunction: KW_INT TK_IDENTIFIER '(' parametersList ')' cmd    {$$ = astCreate(AST_DEC_FUNCTION, $2, $4, $6, 0, 0);}
    | KW_FLOAT TK_IDENTIFIER '(' parametersList ')' cmd         {$$ = astCreate(AST_DEC_FUNCTION, $2, $4, $6, 0, 0);}
    | KW_CHAR TK_IDENTIFIER '(' parametersList ')' cmd          {$$ = astCreate(AST_DEC_FUNCTION, $2, $4, $6, 0, 0);}
    | KW_INT TK_IDENTIFIER '(' ')' cmd                          {$$ = astCreate(AST_DEC_FUNCTION, $2, $5, 0, 0, 0);}
    | KW_FLOAT TK_IDENTIFIER '(' ')' cmd                        {$$ = astCreate(AST_DEC_FUNCTION, $2, $5, 0, 0, 0);}
    | KW_CHAR TK_IDENTIFIER '(' ')' cmd                         {$$ = astCreate(AST_DEC_FUNCTION, $2, $5, 0, 0, 0);}
    ;

parametersList: parameter ',' parametersList        {$$ = astCreate(AST_PARAMETERS_LIST, 0, $1, $3, 0, 0);}
    | parameter                                     {$$ = $1;}
    ;

parameter: KW_INT TK_IDENTIFIER             {$$ = astCreateTerminal($2);}
    | KW_FLOAT TK_IDENTIFIER                {$$ = astCreateTerminal($2);}
    | KW_CHAR TK_IDENTIFIER                 {$$ = astCreateTerminal($2);}
    ;

dec:  KW_INT TK_IDENTIFIER decIntChar       {$$ = astCreate(AST_DEC_INT, astCreateTerminal($2), $3, 0, 0, 0);}
    | KW_CHAR TK_IDENTIFIER decIntChar      {$$ = astCreate(AST_DEC_CHAR, astCreateTerminal($2), $3, 0, 0, 0);}
    | KW_FLOAT TK_IDENTIFIER decFloat       {$$ = astCreate(AST_DEC_FLOAT, astCreateTerminal($2), $3, 0, 0, 0);}
    ;

decIntChar: ':' LIT_INTEGER     {$$ = astCreateTerminal($2);}
    | ':' LIT_CHAR              {$$ = astCreateTerminal($2);}
    | arrayFormat               {$$ = $1;}
    ;

decFloat: ':' LIT_INTEGER '/' LIT_INTEGER   {$$ = astCreate(AST_FLOAT, 0, astCreateTerminal($2), astCreateTerminal($4), 0, 0);}
    | arrayFormat                           {$$ = $1;}    
    ;

arrayFormat: '[' LIT_INTEGER ']' ':' LIT_INTEGER arrayValues    {$$ = astCreate(AST_ARRAY_FORMAT, $2, astCreateTerminal($5), $6, 0, 0);}
    | '[' LIT_INTEGER ']' ':' LIT_CHAR arrayValues              {$$ = astCreate(AST_ARRAY_FORMAT, $2, astCreateTerminal($5), $6, 0, 0);}
    | '[' LIT_INTEGER ']'                                       {$$ = astCreateTerminal($2);}
    ;

arrayValues: LIT_INTEGER arrayValues    {$$ = astCreate(AST_ARRAY_VALUES, $1, $2, 0, 0, 0);}
    | LIT_CHAR arrayValues              {$$ = astCreate(AST_ARRAY_VALUES, $1, $2, 0, 0, 0);}    
    |                                   {$$ = 0;}
    ;

lcmd: cmd ';' lcmd          {$$ = astCreate(AST_LCMD, 0, $1, $3, 0, 0);}
    | label lcmd            {$$ = astCreate(AST_LABEL, 0, $1, $2, 0, 0);}
    |                       {$$ = 0;}
    ;

label: TK_IDENTIFIER ':'    {$$ = astCreateTerminal($1);}
    ;

cmd:  TK_IDENTIFIER '=' expr                    {$$ = astCreate(AST_ATRIBUTION, $1, $3, 0, 0, 0);}
    | TK_IDENTIFIER '[' expr ']' '=' expr       {$$ = astCreate(AST_ATRIBUTION, $1, $3, $6, 0, 0);}
    | KW_PRINT printValues                      {$$ = astCreate(AST_PRINT, 0, $2, 0, 0, 0);}
    | KW_WHILE expr cmd                         {$$ = astCreate(AST_WHILE, 0, $2, $3, 0, 0);}
    | KW_IF expr KW_THEN cmd KW_ELSE cmd        {$$ = astCreate(AST_IF_THEN_ELSE, 0, $2, $4, $6, 0);}
    | KW_IF expr KW_THEN cmd                    {$$ = astCreate(AST_IF_THEN, 0, $2, $4, 0, 0);}
    | KW_GOTO TK_IDENTIFIER                     {$$ = astCreate(AST_GOTO, 0, astCreateTerminal($2), 0, 0, 0);}
    | KW_RETURN expr                            {$$ = astCreate(AST_RETURN, 0, $2, 0, 0, 0);}
    | '{' lcmd '}'                              {$$ = $2;}
    |                                           {$$ = 0;}
    ;

expr: LIT_INTEGER                           {$$ = astCreateTerminal($1);}
    | LIT_CHAR                              {$$ = astCreateTerminal($1);}
    | TK_IDENTIFIER '[' expr ']'            {$$ = astCreate(AST_ARRAY_ELEMENT, $1, $3, 0, 0, 0);}
    | TK_IDENTIFIER '(' listExpr ')'        {$$ = astCreate(AST_FUNCTION_ARGUMENTS, $1, $3, 0, 0, 0);}
    | TK_IDENTIFIER                         {$$ = astCreateTerminal($1);}
    | KW_READ                               {$$ = 0;}
    | '(' expr ')'                          {$$ = $2;}
    | expr OPERATOR_DIF expr                {$$ = astCreate(AST_DIF, 0, $1, $3, 0, 0);}
    | expr OPERATOR_EQ expr                 {$$ = astCreate(AST_EQ, 0, $1, $3, 0, 0);}
    | expr OPERATOR_GE expr                 {$$ = astCreate(AST_GE, 0, $1, $3, 0, 0);}
    | expr OPERATOR_LE expr                 {$$ = astCreate(AST_LE, 0, $1, $3, 0, 0);}
    | expr '+' expr                         {$$ = astCreate(AST_ADD, 0, $1, $3, 0, 0);}
    | expr '-' expr                         {$$ = astCreate(AST_SUB, 0, $1, $3, 0, 0);}    
    | expr '*' expr                         {$$ = astCreate(AST_MULT, 0, $1, $3, 0, 0);}
    | expr '/' expr                         {$$ = astCreate(AST_DIV, 0, $1, $3, 0, 0);}
    | expr '>' expr                         {$$ = astCreate(AST_GREATER, 0, $1, $3, 0, 0);}
    | expr '<' expr                         {$$ = astCreate(AST_LESS, 0, $1, $3, 0, 0);}
    ;

listExpr: expr ',' listExpr         {$$ = astCreate(AST_LIST_EXPR, 0, $1, $3, 0, 0);}
    | expr                          {$$ = $1;}
    ; 

printValues: printParameter ',' printValues     {$$ = astCreate(AST_PRINT_VALUES, 0, $1, $3, 0, 0);}
    | printParameter                            {$$ = $1;}
    ;

printParameter: LIT_STRING      {astCreateTerminal($1);}
    | expr                      {$$ = $1;}
    ;

%%

int yyerror(){
    fprintf(stderr, "Syntax Error Found at line %d \n",getLineNumber());
    exit(3);
}