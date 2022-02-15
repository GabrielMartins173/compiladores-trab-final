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
  FILE *outputFile = 0;
  int token = 0;

  if (argc < 3)
  {
    printf("call: ./etapa1 input.txt output.txt \n");
    exit(1);
  }

  if (0 == (yyin = fopen(argv[1], "r")))
  {
    printf("Cannot open file %s... \n", argv[1]);
    exit(1);
  }
  if (0 == (outputFile = fopen(argv[2], "w+")))
  {
    printf("Cannot open file %s... \n", argv[2]);
    exit(1);
  }

  initMe();

  yyparse();

  printf("Number of Lines on the File: %d\n\n", getLineNumber());
  printf("Number of Errors on the File: %d\n\n", getNumberOfErrors());

  fprintf(outputFile, "Number of Lines on the File: %d\n\n", getLineNumber());
  fprintf(outputFile, "Number of Errors on the File: %d\n\n", getNumberOfErrors());

  printHashTable();
  fprintf(stderr, "Compilation Completed Successfully! \n");
  fprintf(stderr, "\n");

  exit(0);
}
