/*
Autor: Gabriel Martins dos Santos - 00275617
Código baseado na implementação feita pelo professor Marcelo Johann
*/

#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include "decompiler.h"

extern int yylex();
extern char *yytext;
extern FILE *yyin;
extern AST *Root;

extern int isRunning();
extern int getLineNumber();
extern int getNumberOfErrors();
extern void printHashTable();
extern void initMe();

int main(int argc, char **argv)
{

  if (argc < 3)
  {
    printf("call: ./etapa3 input.txt output.txt\n");
    exit(1);
  }

  if (0 == (yyin = fopen(argv[1], "r")))
  {
    printf("Cannot open file %s... \n", argv[1]);
    exit(2);
  }else {
    yyin = fopen(argv[1], "r");
  }

  FILE *fp = fopen(argv[2], "w");

  if(fp == 0) {
    fprintf(stderr, "Cannot open file %s\n", argv[2]);
    exit(2);
  }

  initMe();

  yyparse();

  printHashTable();

  decompile(Root, fp);

  printf("Number of Lines on the File: %d\n\n", getLineNumber());
  printf("Number of Errors on the File: %d\n\n", getNumberOfErrors());

  printf(" \nCompilation Completed Successfully! \n\n");

  exit(0);
}
