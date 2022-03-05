%{

int yyerror();
extern int getLineNumber();

%}

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

%token TK_IDENTIFIER     

%token LIT_INTEGER       
%token LIT_CHAR          
%token LIT_STRING    

%token TOKEN_ERROR

%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF '<' '>'
%left '+' '-'
%left '*' '/'

%%

program: decl
    ;

decl: dec ';' decl
    | decFunction decl
    |
    ;

decFunction: KW_INT TK_IDENTIFIER '(' parametersList ')' cmd
    | KW_FLOAT TK_IDENTIFIER '(' parametersList ')' cmd
    | KW_CHAR TK_IDENTIFIER '(' parametersList ')' cmd
    | KW_INT TK_IDENTIFIER '(' ')' cmd
    | KW_FLOAT TK_IDENTIFIER '(' ')' cmd
    | KW_CHAR TK_IDENTIFIER '(' ')' cmd
    ;

parametersList: parameter ',' parametersList 
    | parameter
    ;

parameter: KW_INT TK_IDENTIFIER
    | KW_FLOAT TK_IDENTIFIER
    | KW_CHAR TK_IDENTIFIER
    ;

dec:  KW_INT TK_IDENTIFIER decIntChar
    | KW_CHAR TK_IDENTIFIER decIntChar
    | KW_FLOAT TK_IDENTIFIER decFloat
    ;

decIntChar: ':' LIT_INTEGER
    | ':' LIT_CHAR
    | arrayFormat
    ;

decFloat: ':' LIT_INTEGER '/' LIT_INTEGER
    | arrayFormat
    ;

arrayFormat: '[' LIT_INTEGER ']' ':' LIT_INTEGER arrayValues
    | '[' LIT_INTEGER ']' ':' LIT_CHAR arrayValues
    | '[' LIT_INTEGER ']'
    ;

arrayValues: LIT_INTEGER arrayValues
    | LIT_CHAR arrayValues
    |
    ;

lcmd: cmd ';' lcmd
    | label lcmd
    |
    ;

label: TK_IDENTIFIER ':'
    ;

cmd:  TK_IDENTIFIER '=' expr
    | TK_IDENTIFIER '[' expr ']' '=' expr
    | KW_PRINT printValues
    | KW_WHILE expr cmd
    | KW_IF expr KW_THEN cmd KW_ELSE cmd
    | KW_IF expr KW_THEN cmd
    | KW_GOTO TK_IDENTIFIER
    | KW_RETURN expr
    | '{' lcmd '}'
    |
    ;

expr: LIT_INTEGER
    | LIT_CHAR
    | TK_IDENTIFIER '[' expr ']'
    | TK_IDENTIFIER '(' listExpr ')'
    | TK_IDENTIFIER
    | KW_READ
    | '(' expr ')'
    | expr OPERATOR_DIF expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_LE expr
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '>' expr
    | expr '<' expr
    ;

listExpr: expr ',' listExpr
    | expr
    ; 

printValues: printParameter ',' printValues
    | printParameter
    ;

printParameter: LIT_STRING
    | expr
    ;

%%

int yyerror(){
    fprintf(stderr, "Syntax Error Found at line %d \n",getLineNumber());
    exit(3);
}