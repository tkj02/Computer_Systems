#include "vertices.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

struct Graph {
	uint32_t vertices; // Number of vertices.
	bool undirected; // Undirected graph?
	bool visited[VERTICES]; // Where have we gone?
	uint32_t matrix[VERTICES][VERTICES]; // Adjacency matrix.
};

Graph *graph_create(uint32_t vertices, bool undirected){
	Graph *G = (Graph *)calloc(1, sizeof(Graph));
	G -> vertices = vertices;
	G -> undirected = undirected;
	return G;
}

void graph_delete(Graph **G){
	free(*G);
	*G = NULL;
	return;
}

uint32_t graph_vertices(Graph *G){
	G -> vertices = vertices;
	return G;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k){
	return;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j){
	return;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j){
        return;
}

bool graph_visited(Graph *G, uint32_t v){
        return;
}

void graph_mark_visited(Graph *G, uint32_t v){
        return;
}

void graph_mark_unvisited(Graph *G, uint32_t v){
        return;
}

void graph_print(Graph *G){
        return;
}

