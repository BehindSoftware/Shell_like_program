#Compiler 
CC=gcc
#Compiler parameters
CFLAGS=-c -Wall

TARGET=similar_shell

OBJ=similar_shell.o #queue.o

all: $(TARGET)
	
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(OBJ): similar_shell.h similar_shell.c queue.h queue.c
	$(CC) $(CFLAGS) similar_shell.c queue.c
	
clean: 
	rm -rf *o $(TARGET)

