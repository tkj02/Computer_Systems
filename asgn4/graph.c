#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    uint32_t vertices; // Number of vertices.
    bool undirected; // Undirected graph?
    bool visited[VERTICES]; // Where have we gone?
    uint32_t matrix[VERTICES][VERTICES]; // Adjacency matrix.
} Graph;

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    if (G) {
        G->vertices = vertices;
        G->undirected = undirected;
    }
    return G;
}

void graph_delete(Graph **G) {
    void free(void *G);
    *G = NULL;
    return;
}
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i > G->vertices || j > G->vertices) {
        return false;
    }
    G->matrix[i][j] = k;
    return true;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i < G->vertices && j < G->vertices && G->matrix[i][j] > 0) {
        return true;
    }
    return false;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i < G->vertices && j < G->vertices && G->matrix[i][j] > 0) {
        return G->matrix[i][j];
    }
    return 0;
}

bool graph_visited(Graph *G, uint32_t v) {
    if (G->visited[v]) {
        return true;
    }
    return false;
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v > G->vertices) {
        G->visited[v] = true;
    }
    G->visited[v] = false;
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v > G->vertices) {
        G->visited[v] = false;
    }
    G->visited[v] = true;
}

void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%u ", G->matrix[i][j]);
        }
        printf("\n");
    }
}
