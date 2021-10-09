CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: mathlib-test

mathlib-test: mathlib-test.o e.o euler.o madhava.o newton.o bbp.o viete.o	
	$(CC) -o mathlib-test mathlib-test.o e.o euler.o madhava.o newton.o bbp.o viete.o $(LFLAGS)

mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -o mathlib-test.o -c mathlib-test.c

e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -o e.o -c e.c

euler.o: euler.c mathlib.h
	$(CC) $(CFLAGS) -o euler.o -c euler.c

madhava.o: madhava.c mathlib.h
	$(CC) $(CFLAGS) -o madhava.o -c madhava.c

newton.o: newton.c mathlib.h
	$(CC) $(CFLAGS) -o newton.o -c newton.c
	
bbp.o: bbp.c mathlib.h
	$(CC) $(CFLAGS) -o bbp.o -c bbp.c

viete.o: viete.c mathlib.h
	$(CC) $(CFLAGS) -o viete.o -c viete.c

clean:
	rm -f mathlib-test.o e.o euler.o madhava.o newton.o bbp.o viete.o

format:
	clang-format -i -style=file *.[ch]



