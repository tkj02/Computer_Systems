CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: banhammer

banhammer: banhammer.o ht.o bst.o node.o bf.o bv.o speck.o parser.o
	$(CC) -o banhammer banhammer.o ht.o bst.o node.o bf.o bv.o speck.o parser.o $(LFLAGS)

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -o banhammer.o -c banhammer.c

ht.o: ht.c ht.h
	$(CC) $(CFLAGS) -o ht.o -c ht.c

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -o bst.o -c bst.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -o node.o -c node.c

bf.o: bf.c bf.h
	$(CC) $(CFLAGS) -o bf.o -c bf.c

bv.o: bv.c bv.h
	$(CC) $(CFLAGS) -o bv.o -c bv.c

speck.o: speck.c speck.h
	$(CC) $(CFLAGS) -o speck.o -c speck.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -o parser.o -c parser.c

clean:
	rm -f banhammer banhammer.o ht.o bst.o node.o bf.o bv.o speck.o parser.o

format:
	clang-format -i -style=file *.[ch]

