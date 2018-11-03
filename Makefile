#Compiler 
CC=gcc
#Compiler parameters
CFLAGS=-c -Wall

all: similar_shell
	
similar_shell: similar_shell.o
	$(CC) similar_shell.o -o similar_shell

similar_shell.o: similar_shell.h similar_shell.c
	$(CC) $(CFLAGS) similar_shell.c

clean: 
	rm -rf *o similar_shell

