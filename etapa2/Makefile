#Autor: Gabriel Martins dos Santos - 00275617

etapa2: clean y.tab.c lex.yy.c hash.c main.c
		gcc -o etapa2 lex.yy.c

y.tab.c: parser.y
	yacc parser.y -d

lex.yy.c: scanner.l
		lex scanner.l

clean:
		rm -f lex.yy.c y.tab.c y.tab.h etapa2
