#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Path {
    Stack *vertices; // The vertices comprising the path.
    uint32_t length; // The total length of the path.
} Path;

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p != NULL) {
        p->vertices = stack_create(VERTICES);
        p->length = 0;
    }
    return p;
}

void path_delete(Path **p) {
    stack_delete(&((*p)->vertices));
    free(*p);
    *p = NULL;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    bool return_stat;
    if (stack_empty(p->vertices)) {
        return stack_push(p->vertices, v);
    } else {
        uint32_t current_top;
        return_stat = stack_peek(p->vertices, &current_top);
        stack_push(p->vertices, v);
        if (return_stat) {
            p->length += graph_edge_weight(G, current_top, v);
            return true;
        }
        return false;
    }
    return false;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t x = 0;
    *v = 0;
    bool return_stat;
    uint32_t current_top;
    uint32_t stack_top;
    return_stat = stack_pop(p->vertices, &x);
    if (return_stat) {
        *v = x;
        stack_top = stack_peek(p->vertices, &current_top);
        p->length -= graph_edge_weight(G, x, stack_top);
        return true;
    }
    return false;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %d \nPath: ", p->length);
    stack_print(p->vertices, outfile, cities);
}
