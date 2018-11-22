#Compiler 
CC=gcc
#Compiler parameters
CFLAGS=-c -Wall
#CFLAGS   = -g -D__GNUEABI__ -fstack-protector-all -Wstack-protector -O3
TARGET=similar_shell

OBJ=similar_shell.o queue.o

all: similar_shell

clean:
		rm -f *.o *~ similar_shell

%.o: %.c %.h similar_shell.h
		$(CC) $(CFLAGS) -c $<

similar_shell: $(OBJ) 
		$(CC) -O2 $(OBJ) -o similar_shell 
		chmod 777 similar_shell
		cp similar_shell /work/users/saydamb/similar_shell
