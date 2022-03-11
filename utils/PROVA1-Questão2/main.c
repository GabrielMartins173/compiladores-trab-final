/* Autor Gabriel Martins dos Santos - 00275617 */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

extern int yylex();
extern char *yytext;
extern FILE *yyin;

extern int isRunning();
extern int isA_Scope();
extern int isB_Scope();
extern int getLineNumber();
extern int getNumberOfErrors();

int main(int argc, char **argv)
{
  FILE *outputFile = 0;
  int token = 0;

  if (argc < 3)
  {
    printf("call: ./questao2 input.txt output.txt \n");
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

  while (isRunning())
  {
    token = yylex();

    if (!isRunning())
    {
      break;
    }

    if (token != TOKEN_ERROR)
    {
      if (isA_Scope())
      {
        if (LIT_LING_A == token || IDENTIFIER_LING_A == token)
        {
          fprintf(outputFile, "Key: %s is present at language A\n", yytext);
        }
        else
        {
          if (LIT_LING_B == token || IDENTIFIER_LING_B == token)
          {
            fprintf(outputFile, "\nERROR at line %d -> Trying to use something from language B inside scope of language A \n", getLineNumber());
          }
        }
      }
      else
      {
        if (isB_Scope())
        {
          if (LIT_LING_B == token || IDENTIFIER_LING_B == token)
          {
            fprintf(outputFile, "Key: %s is present at language B\n", yytext);
          }
          else
          {
            if (LIT_LING_A == token || IDENTIFIER_LING_A == token)
            {
              fprintf(outputFile, "\nERROR at line %d -> Trying to use something from language A inside scope of language B \n", getLineNumber());
            }
          }
        }
      }
    }
    else
    {
      fprintf(outputFile, "\nINVALID INPUT: %s \n", yytext);
    }
  }

  fprintf(outputFile, "\n\nNumber of Lines on the File: %d\n\n", getLineNumber());
  fprintf(outputFile, "Number of Non Recognized elements on the File: %d", getNumberOfErrors());

  exit(0);
}