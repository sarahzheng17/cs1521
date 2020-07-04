# COMP1521 19T3 ... lab 1

CC	= gcc
CFLAGS	= -Wall -Werror -std=gnu11 -g

.PHONY:	all
all:	cat1 cat2 cat3 cat4

cat1:	cat1.o
cat2:	cat2.o
cat3:	cat3.o
cat4:	cat4.o

.PHONY: clean
clean:
	-rm -f cat1 cat1.o
	-rm -f cat2 cat2.o
	-rm -f cat3 cat3.o
	-rm -f cat4 cat4.o

.PHONY: give
give: cat1.c cat2.c cat3.c cat4.c
	give cs1521 lab01_mycat $^
