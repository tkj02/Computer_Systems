#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS     "hvui:o:"
#define BUFFERSIZE  100
#define CITYNAMELEN 64

// DFS Function
// Conducts Depth-first Search to find paths
void dfs(Graph *G, uint32_t v, Path *current, Path *shortest, char *cities[], FILE *outfile) {
    graph_mark_visited(G, v);
    //printf("in dfs v %d\n", v);
    for (uint32_t w = 0; w < graph_vertices(G); w++) {
        uint32_t weight = graph_edge_weight(G, v, w);
        //printf("v %d w %d weight %d\n", v, w, weight);
        if (weight == 0) {
            continue;
        }
        if (graph_visited(G, w)) {
            continue;
        }
        //printf("pushing vertice %d\n", v);
        dfs(G, w, current, shortest, cities, outfile);
        path_push_vertex(current, v, G);
    }
    graph_mark_unvisited(G, v);
}

// Own strdup() Function
// Removes extra newline character
int fgetscopy(char *dst, char *src) {
    char ch;
    while ((ch = *src)) {
        if ((ch == '\n') || (ch == '\r')) {
            *dst = 0;
            break;
        }
        *dst = *src;
        dst++;
        src++;
    }
    *dst = 0;
    return 0;
}

// Main Function
int main(int argc, char **argv) {

    // Initializes necessary variables
    int opt = 0;
    bool no_input = true;
    bool undirected = false;
    FILE *fp = stdin;
    FILE *outfp = stdout;
    char buffer[BUFFERSIZE];
    char *retptr;
    int vertexcount;
    char *cities_ar;
    uint32_t node_i, node_j, node_k;
    Graph *gptr;
    Path *current_path;
    Path *shortest_path;

    // getopt function
    // Checks command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input = false;
        switch (opt) {
        case 'h':
            // Prints help message
            printf("SYNOPSIS\n  Traveling Salesman Problem using DFS.\n\n");
            printf("USAGE\n  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -u             Use undirected graph.\n");
            printf("  -v             Enable verbose printing.\n");
            printf("  -h             Program usage and help.\n");
            printf("  -i infile      Input containing graph (default: stdin)\n");
            printf("  -o outfile     Output of computed path (default: stdout)\n");
        case 'v':
            // Prints all paths
        case 'u':
            // Specifies graph to be undirected
            undirected = true;
        case 'i':
            // Specifies input file
            fp = fopen(optarg, "r");
            if (fp == NULL) {
                printf("error opening file %s\n", optarg);
            }
            break;
        case 'o':
            // Specifies output file
            outfp = fopen(optarg, "w");
            if (outfp == NULL) {
                printf("error file write %s\n", optarg);
                goto errorexit;
            }
            break;
        }
    }

    // Allocates needed memory to support cities   
    retptr = fgets(buffer, BUFFERSIZE, fp);
    sscanf(buffer, "%d", &vertexcount);
    cities_ar = malloc(CITYNAMELEN * vertexcount);

    if (vertexcount < 1 || vertexcount > VERTICES) {
        printf("invalid vertices\n");
        goto errorexit;
    }

    // Sets up cities and allocates needed memory
    char **cities;
    cities = malloc(sizeof(char *) * vertexcount);
    for (int i = 0; i < vertexcount; i++) {
        retptr = fgets(buffer, BUFFERSIZE, fp);
        if (retptr == NULL) {
            goto errorexit;
        }
        fgetscopy(&cities_ar[i * CITYNAMELEN], buffer);
        cities[i] = &cities_ar[i * CITYNAMELEN];
    }

    // Creates graph and checks conditions for i, j, and k
    gptr = graph_create(vertexcount, undirected);
    while (1) {
        retptr = fgets(buffer, BUFFERSIZE, fp);
        if (retptr == NULL) {
            break;
        }
        sscanf(buffer, "%d %d %d", &node_i, &node_j, &node_k);
        if (node_i < 0 || node_i > VERTICES || node_j < 0 || node_j > VERTICES) {
            printf("invalid matrix values\n");
            goto errorexit;
        }
        graph_add_edge(gptr, node_i, node_j, node_k);
    }

    // Creates paths for current and shortest
    current_path = path_create();
    shortest_path = path_create();

    // Calls DFS and prints path information
    dfs(gptr, START_VERTEX, current_path, shortest_path, cities, outfp);
    path_push_vertex(current_path, START_VERTEX, gptr);
    path_print(current_path, outfp, cities);
    printf("Total recursive calls: \n");

    //Frees memory
    path_delete(&current_path);
    path_delete(&shortest_path);
    graph_delete(&gptr);

// Closes file if error present
errorexit:
    if (fp != stdin) {
        fclose(fp);
    }
    return 0;
}
