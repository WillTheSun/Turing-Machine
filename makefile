CC = gcc
CFLAGS = -g3 -pg -std=c99 -Wall -pedantic 
turing: turing.o
	${CC} ${CFLAGS} -o $@ $^

