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

%%

program: decl
    ;

decl: dec closeDecl
    | decFunction closeFunc
    |
    ;
    
closeDecl: ';' decl 
    |
    ;

closeFunc: decl
    ;

decFunction: KW_INT TK_IDENTIFIER '(' parametersList ')' body
    | KW_FLOAT TK_IDENTIFIER '(' parametersList ')' body
    | KW_CHAR TK_IDENTIFIER '(' parametersList ')' body
    ;

parametersList:  parameter ',' parametersList
    | parameter
    |
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

body: '{' lcmd '}'
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
    | KW_WHILE expr body
    | KW_IF expr KW_THEN bodyIf
    | KW_IF expr KW_THEN cmd
    | KW_GOTO TK_IDENTIFIER
    | KW_RETURN expr
    ;

bodyIf: body KW_ELSE body
    | body KW_ELSE cmd
    | body
    ;

expr: characterLiterals
    | TK_IDENTIFIER '[' expr ']'
    | TK_IDENTIFIER '(' listExpr ')'
    | TK_IDENTIFIER
    | KW_READ
    | '(' expr ')'
    | expr operator expr
    ;

characterLiterals: LIT_CHAR
    | LIT_INTEGER
    ; 

operator: OPERATOR_DIF
    | OPERATOR_EQ
    | OPERATOR_GE
    | OPERATOR_LE
    | '+'
    | '-'
    | '*'
    | '/'
    | '%'
    | '<'
    | '>'
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
    fprintf(stderr, "Syntax Error. \n");
    printf("Error Found at line %d \n",getLineNumber());
    exit(3);
}