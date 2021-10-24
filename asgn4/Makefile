CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: tsp

tsp: tsp.o graph.o stack.o path.o
	$(CC) -o tsp tsp.o graph.o stack.o path.o $(LFLAGS)

tsp.o: tsp.c
	$(CC) $(CFLAGS) -o tsp.o -c tsp.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -o graph.o -c graph.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -o stack.o -c stack.c

path.o: path.c path.h
	$(CC) $(CFLAGS) -o path.o -c path.c

clean:
	rm -f tsp tsp.o graph.o path.o stack.o

format:
	clang-format -i -style=file *.[ch]


