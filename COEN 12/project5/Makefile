CC	= gcc
CFLAGS	= -g -Wall
PROGS	= sort huffman

.PHONY: all
all:		$(PROGS)

.PHONY: clean
clean:
	$(RM) $(PROGS) *.o core

sort:		sort.o pqueue.o
		$(CC) $(CFLAGS) -o sort sort.o pqueue.o
.PHONY: sort

huffman:	huffman.o pqueue.o pack.o
		$(CC) $(CFLAGS) -o huffman huffman.o pqueue.o pack.o
.PHONY: huffman

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@