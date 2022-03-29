#Autor: Gabriel Martins dos Santos - 00275617

ETAPA=etapa4

etapa4:  main.o y.tab.o lex.yy.o hash.o ast.o decompiler.o semantic.o
	gcc  main.o y.tab.o lex.yy.o hash.o ast.c decompiler.c semantic.c -o $(ETAPA)

main.o: main.c
	gcc -c main.c

decompiler.o: decompiler.c
	gcc -c decompiler.c

semantic.o: semantic.c
	gcc -c semantic.c

hash.o: hash.c
	gcc -c hash.c
	
ast.o: ast.c
	gcc -c ast.c

y.tab.o: y.tab.c 
	gcc -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.c
	lex scanner.l

build:
	make clean --no-print-directory
	make --no-print-directory

test:
	./$(ETAPA) tests/input.txt tests/output.txt
	./$(ETAPA) tests/output.txt tests/final.txt      
	diff tests/output.txt tests/final.txt 

test2:
	./$(ETAPA) tests/input2.txt tests/output2.txt
	./$(ETAPA) tests/output2.txt tests/final2.txt      
	diff tests/output2.txt tests/final2.txt  

test3:
	./$(ETAPA) tests/input3.txt tests/output3.txt
	./$(ETAPA) tests/output3.txt tests/final3.txt      
	diff tests/output3.txt tests/final3.txt  

tar:
	tar cvzf $(ETAPA).tgz .

send:
	scp $(ETAPA).tgz  gmsantos@html.inf.ufrgs.br:public_html/dcpzdbtrupcwoptq/
	chmod 744 $(ETAPA).tgz

connect: 
	sftp gmsantos@html.inf.ufrgs.br

clean:
	rm -f scanner.c lex.yy.c y.tab.c y.tab.h *.o $(ETAPA)
