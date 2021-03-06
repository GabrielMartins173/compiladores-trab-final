/*
Autor: Gabriel Martins dos Santos - 00275617
Código baseado na implementação feita pelo professor Marcelo Johann
*/

#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

extern int yylex();
extern char *yytext;
extern FILE *yyin;

extern int isRunning();
extern int getLineNumber();
extern int getNumberOfErrors();
extern void printHashTable();
extern void initMe();

int main(int argc, char **argv)
{
  int token = 0;

  if (argc < 2)
  {
    printf("call: ./etapa1 input.txt \n");
    exit(1);
  }

  if (0 == (yyin = fopen(argv[1], "r")))
  {
    printf("Cannot open file %s... \n", argv[1]);
    exit(2);
  }else {
    yyin = fopen(argv[1], "r");
  }

  initMe();

  yyparse();

  printHashTable();

  printf("Number of Lines on the File: %d\n\n", getLineNumber());
  printf("Number of Errors on the File: %d\n\n", getNumberOfErrors());

  printf(" \nCompilation Completed Successfully! \n\n");

  exit(0);
}
