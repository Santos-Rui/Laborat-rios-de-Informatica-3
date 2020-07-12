SHELL := /bin/bash

CC = gcc 

CFLAGS = -ansi -g -Wall -Wextra -pedantic -O2

#all: doc compress clean



all: trie.o client_cat.o product_cat.o product_accounting.o accounting.o purchases.o main clean



clean: 
	@echo "A limpar diretoria...."
	rm -rf trunk/*.o


clean_exec:
	@echo "A eliminar executável...."
	rm -f main 

############################## - Documentação - #########################################
##analise.pdf:  report/rel.tex 
##       pdflatex report/rel.tex pdflatex report/rel.tex pdflatex
##       #       report/rel.tex mv rel.pdf analise.pdf rm -fr rel.* rm -fr
##       report/chapters/*.aux #rm -r report
#
#
#compress: identificacao  ./trunk ./doc
#	@echo "Preparar ficheiro Bzip para entrega...."
#	#tar jcf PLg039-et1.tar.bz2 identificacao analise.pdf trunk doc
#	#tar jcf PLg039-et1.tar.bz2 identificacao trunk doc
#	tar jcf PLg039-et2.tar.bz2 identificacao trunk doc
#

################################ - MAIN - ###########################################
main: ./trunk/trie.o ./product_accounting.o ./trunk/accounting.o ./trunk/client_cat.o ./trunk/string_array.o ./trunk/abin.o ./trunk/avl.o ./trunk/product_cat.o ./trunk/io.o  ./trunk/main.o 
	@echo "A compilar MAIN...."
	$(CC) $(CFLAGS) ./trunk/product_cat.o ./trunk/string_array.o ./trunk/client_cat.o ./trunk/product_accounting.o ./trunk/accounting.o ./trunk/purchases.o ./trunk/trie.o ./trunk/io.o ././trunk/abin.o ./trunk/avl.o ./trunk/main.o -o main

main.o: ./trunk/trie.h ./trunk/client_cat.h ./trunk/product_cat.h ./trunk/io.h ./trunk/accounting.h ./trunk/main.c
	$(CC) $(CFLAGS) -c ./trunk/main.c
################################ - MÓDULOS DE FUNÇÔES - ###########################################


io.o: ./trunk/io.h ./trunk/io.c ./trunk/trie.h ./trunk/client_cat.h ./trunk/product_cat.h ./trunk/io.h ./trunk/accounting.h ./trunk/main.c
	 $(CC) $(CFLAGS) -c ./trunk/io.c

################################ - MÓDULOS - ###########################################

purchases.o: ./trunk/trie.h ./trunk/purchases.h ./trunk/purchases.c
	$(CC) $(CFLAGS) -c ./trunk/purchases.c -o ./trunk/purchases.o

product_cat.o: ./trunk/trie.h ./trunk/product_cat.c ./trunk/product_cat.h
	$(CC) $(CFLAGS) -c ./trunk/product_cat.c -o ./trunk/product_cat.o

client_cat.o: ./trunk/trie.h ./trunk/client_cat.c ./trunk/client_cat.h
	$(CC) $(CFLAGS) -c ./trunk/client_cat.c -o ./trunk/client_cat.o

accounting.o: ./trunk/trie.h ./trunk/accounting.c ./trunk/accounting.h
	$(CC) $(CFLAGS) -c ./trunk/accounting.c -o ./trunk/accounting.o

product_accounting.o: ./trunk/product_accounting.h ./trunk/product_accounting.c ./trunk/bool.h
	$(CC) $(CFLAGS) -c ./trunk/product_accounting.c -o ./trunk/product_accounting.o
################################ - ESTRUTURAS BASE - ###########################################
abin.o: ./trunk/abin.h ./trunk/abin.c
	$(CC) $(CFLAGS) -c ./trunk/abin.c -o ./trunk/abin.o

avl.o: ./trunk/avl.h ./trunk/avl.c 
	$(CC) $(CFLAGS) -c ./trunk/avl.c  -o ./trunk/avl.o

trie.o: ./trunk/trie.c ./trunk/trie.h 
	$(CC) $(CFLAGS) -c ./trunk/trie.c -o ./trunk/trie.o

string_array.o: ./trunk/string_array.h ./trunk/string_array.c
	$(CC) $(CFLAGS) -c ./trunk/string_array.c -o ./trunk/string_array.o
