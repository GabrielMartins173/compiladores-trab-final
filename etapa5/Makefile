#Autor: Gabriel Martins dos Santos - 00275617

ETAPA=etapa5

etapa5:  main.c y.tab.c lex.yy.c 
	gcc -g main.c y.tab.c lex.yy.c hash.c ast.c decompiler.c semantic.c -o $(ETAPA)

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
