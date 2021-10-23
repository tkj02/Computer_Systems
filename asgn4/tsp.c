#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <unistd.h>

#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#define OPTIONS "hvui:o:"

static FILE *input = NULL;
static FILE *output = NULL;

int main(int argc, char** argv){
	int opt = 0;
	bool no_input = true;
	bool undirected = false;
	uint32_t vertices = 0;
	char *input_file = NULL;
	char *output_file = NULL;

	while ((opt = getopt(argc, argv, OPTIONS)) != -1){
		no_input = false;
		switch(opt){
			case 'h':
				//print message
			case 'v':
				//print all paths
			case 'u':
				//specify graph to be undirected
			case 'i':
				//specify input file
				input_file = optarg;
				break;
			case 'o':
				//specify output file
				input_file = optarg;
				break;
		}
	}

	input = stdin;
	output = stdout;

	Graph *locations = graph_create(vertices, undirected);
	
	if (locations == NULL){
		//print error to stderr, clean memory, delete functions
		//return 1 
	}
	//call path_create, call dfs
	//print shortest path
	//clean memory
	
	return 0;
}









