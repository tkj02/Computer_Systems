CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: encoder decoder

encoder decoder: encoder.o decoder.o node.o pq.o code.o io.o stack.o huffman.o
	$(CC) -o encoder decoder encoder.o decoder.o node.o pq.o code.o io.o stack.o huffman.o

encoder.o decoder.o: encoder.c decoder.c
	$(CC) $(CFLAGS) -o encoder.o decoder.o encoder.c decoder.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -o node.o -c node.c

pq.o: pq.c pq.h
	$(CC) $(CFLAGS) -o pq.o -c pq.c

code.o: code.c code.h
	$(CC) $(CFLAGS) -o code.o -c node.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -o io.o -c io.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -o stack.o -c stack.c

huffman.o: huffman.c huffman.h
	$(CC) $(CFLAGS) -o huffman.o -c huffman.c

clean:
	rm -f encoder decoder encoder.o decoder.o node.o pq.o code.o io.o stack.o huffman.o

format:
	clang-format -i -style=file *.[ch]

