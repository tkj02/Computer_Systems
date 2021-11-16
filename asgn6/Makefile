CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

all: keygen encrypt decrypt

keygen: keygen.o numtheory.o randstate.o rsa.o
	$(CC) -o keygen keygen.o numtheory.o randstate.o rsa.o $(LFLAGS)

encrypt: encrypt.o numtheory.o randstate.o rsa.o
	 $(CC) -o encrypt encrypt.o numtheory.o randstate.o rsa.o $(LFLAGS)

decrypt: decrypt.o numtheory.o randstate.o rsa.o
	$(CC) -o decrypt decrypt.o numtheory.o randstate.o rsa.o $(LFLAGS)

numtheory.o: numtheory.c numtheory.h
	$(CC) $(CFLAGS) -o numtheory.o -c numtheory.c

randstate.o: randstate.c randstate.h
	$(CC) $(CFLAGS) -o randstate.o -c randstate.c

rsa.o: rsa.c rsa.h
	$(CC) $(CFLAGS) -o rsa.o -c rsa.c

clean:
	rm -f keygen encrypt decrypt keygen.o encrypt.o decrypt.o numtheory.o randstate.o rsa.o

format:
	clang-format -i -style=file *.[ch]
