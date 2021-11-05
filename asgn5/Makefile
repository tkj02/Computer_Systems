CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: encode decode

encode: encode.o node.o code.o stack.o pq.o huffman.o io.o
	$(CC) -o encode encode.o node.o code.o stack.o pq.o huffman.o io.o $(LFLAGS)

decode: decode.o node.o code.o stack.o pq.o huffman.o io.o
	$(CC) -o decode decode.o node.o code.o stack.o pq.o huffman.o io.o $(LFLAGS)

encode.o: encode.c
	$(CC) $(CFLAGS) -o encode.o -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -o decode.o -c decode.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -o node.o -c node.c

code.o: code.c code.h
	$(CC) $(CFLAGS) -o code.o -c code.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -o stack.o -c stack.c

pq.o: pq.c pq.h
	$(CC) $(CFLAGS) -o pq.o -c pq.c

huffman.o: huffman.c huffman.h
	$(CC) $(CFLAGS) -o huffman.o -c huffman.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -o io.o -c io.c

clean:
	rm -f encode decode encode.o decode.o node.o pq.o code.o io.o stack.o huffman.o

format:
	clang-format -i -style=file *.[ch]

