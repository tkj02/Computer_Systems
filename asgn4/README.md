Assignment 4 - The Perambulations of Denver Long

Purpose: The purpose of this assignment is to implement Hamiltonian paths, where all vertices of a graph will be visited only once and the starting vertex is the same as the ending vertex. Three files, graph.c, stack.c, and path.c, contain functions that can create and manipulate the necessary graphs, stacks, and paths for this purpose. The functions implemented in each file are used in the main test harness (tsp.c), where path progression, path length, and the total number of recursive calls can be displayed when run. Users have the option to enter command line arguments -h, -v, -u, -i, and -o and try out their own paths with unique locations and edge weights.

Build and Run: To compile the main test harness tsp.c and create the executable file tsp, run `$ make` or `$ make all`. Then run `$ ./tsp` with any combination of the command line arguments h, v, u, i, and/or o. Arguments i and o can take on file names provided by the user (for example, `$ ./tsp -i ucsc.graph` runs tsp with an infile called ucsc.graph that has predetermined locations and edge weights).

Files:
- graph.h specifies the interface to the graph abstract data type
- graph.c implements the graph abstract data type 
- path.h specifies the interface to the path abstract data type
- path.c implements the path abstract data type
- stack.h specifies the interface to the stack abstract data type
- stack.c implements the stack abstract data type
- tsp.c contains main() and other necessary functions for running the program
- vertices.h defines macros regarding vertices
- Makefile information for compiling, formatting, and removing .o files and executables
- README.md describes program and Makefile
- DESIGN.pdf includes design/design process, pseudocode, and explanations 

Command Line Arguments:
- h: prints help message describing the purpose of the graph and the command-line options it accepts, exiting the program afterwards
- v: enables verbose printing (prints all Hamiltonian paths found as well as the total number of recursive calls to dfs)
- u: specifies that the graph should be undirected
- i (infile): specifies the input file path that has locations and edges of a graph (default is set as stdin)
- o (outfile): specifies the output file path that the program prints to (default output is set as stdout)

Example Graph Files (contain predetermined locations and edge weights):
- diego.graph
- mythical.graph
- short.graph
- solarsystem.graph
- texas.graph
- ucsc.graph

Assistance:
- Watch Eugene’s recorded section on YuJa (learned about the assignment overall, how the graphs are set up, and how the stack works)
- Watched part of Chrtisian’s recorded section on YuJa (got ideas on how to implement tsp.c and how to set up parameters when calling functions)
- Attended Brian’s section on October 22 (learned about pushing and popping and how to decipher the example executable)
- Learned about pointers vs ampersands as well as when to use which from my dad
- Consulted this website (https://www.tutorialspoint.com/data_structures_algorithms/depth_first_traversal.htm) to learn how DFS works

Citations:
- Assignment document: I followed the pseudocode provided on the assignment document for the following portions of my code:
    - struct graph (page 3)
    - graph_create (page 4)
    - graph_delete (page 4)
    - DFS (page 6)
    - struct stack (page 7)
    - stack_create (page 7)
    - stack_delete (page 7)
    - stack_print (page 9)
    - path_print (page 9)
    - DFS function prototype set up (page 12)

There are no known bugs/errors according to scan-build.
