CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: sorting

sorting: sorting.o insert.o heap.o shell.o quick.o
	$(CC) -o sorting sorting.o insert.o heap.o shell.o quick.o $(LFLAGS)

sorting.o: sorting.c stats.h
	$(CC) $(CFLAGS) -o sorting.o -c sorting.c

insert.o: insert.c stats.h
	$(CC) $(CLFAFS) -o insert.o -c insert.c

heap.o: heap.c stats.h
	$(CC) $(CLFAFS) -o heap.o -c heap.c

shell.o: heap.c stats.h
	$(CC) $(CLFAFS) -o shell.o -c shell.c

quick.o: quick.c stats.h
	$(CC) $(CLFAFS) -o quick.o -c quick.c

clean:
	rm -f sorting sorting.o insert.o heap.o shell.o quick.o

format:
	clang-format -i -style=file *.[ch]
