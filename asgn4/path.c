#include <stdbool.h>
#include <stdio.h>

struct Path {
	Stack *vertices; // The vertices comprising the path.
	uint32_t length; // The total length of the path.
};

Path *path_create(void){
	return;
}

void path_delete(Path **p){
	return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G){
	return;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G){
	return;
}

uint32_t path_vertices(Path *p){
	return;
}

uint32_t path_length(Path *p){
	return;
}

void path_copy(Path *dst, Path *src){
	return;
}

void path_print(Path *p, FILE *outfile, char *cities[]){
	return;
}
