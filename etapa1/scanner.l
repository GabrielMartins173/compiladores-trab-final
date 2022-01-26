%%
int            {printf("Hello World");}

%%

int yywrap(){return 1;}

int main(){
    yylex();
}