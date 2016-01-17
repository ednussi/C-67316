.PHONY: all clean
# Object declarations
FLAGS = -std=c99 -Wall -Wextra -Wvla
CC = gcc
LINKAGE_SEPERATLY = -c

########################################################
all: sudukusolver genericdfs.a
	 tar cvf ex3.tar sudukusolver.c genericdfs.c sudukutree.c sudukutree.h makefile

sudukusolver: sudukusolver.o genericdfs.o sudukutree.o
	$(CC) -g $(FLAGS) sudukusolver.o genericdfs.o sudukutree.o -o  sudukusolver -lm

sudukusolver.o: sudukusolver.c sudukutree.h
	$(CC) -g $(LINKAGE_SEPERATLY) $(FLAGS) sudukusolver.c
	
genericdfs.o: genericdfs.c
	$(CC) -g $(LINKAGE_SEPERATLY) $(FLAGS) genericdfs.c

genericdfs.a: genericdfs.o
	ar rcs genericdfs.a genericdfs.o
	
sudukutree.o: sudukutree.c sudukutree.h
	$(CC) -g $(LINKAGE_SEPERATLY) $(FLAGS) sudukutree.c

clean:
	rm -f *.o sudukusolver genericdfs.a
