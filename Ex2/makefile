#Objects
CC = gcc
CFLAGS = -Wextra -Wall

# makefile
waredb : waredb.c
	$(CC) $(CFLAGS) waredb.c -o waredb

waredb.o: waredb.c
	$(CC) -c waredb.c

CheckParenthesis : CheckParenthesis.c
	$(CC) $(CFLAGS) CheckParenthesis.c -o CheckParenthesis

CheckParenthesis.o: CheckParenthesis.c
	$(CC) -c CheckParenthesis.c

# all
all: waredb CheckParenthesis

# clean
clean:
	rm -f waredb CheckParenthesis *.o

.PHONY: all clean
