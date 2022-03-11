#Autor: Gabriel Martins dos Santos - 00275617

questao2: lex.yy.c
		gcc -o questao2 lex.yy.c
lex.yy.c: scanner.l
		lex scanner.l

run: 	
		./questao2 input.txt output.txt

clean:
		rm lex.yy.c questao2 output.txt
