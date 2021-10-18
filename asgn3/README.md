Assignment 2 - Sorting: Putting Your Affairs in Order

Purpose: The purpose of this assignment is to implement sorting algorithms that will sort arrays of various elements and sizes. There are four different sorting implementations provided in their respective files in this repository (insert.c for insertion sort, heap.c for heap sort, shell.c for shell sort, and quick.c for quick sort). sorting.c uses the code contained in each file to then display the results as well as the efficiency of these algorithms using command line arguments.

Build and Run: To compile sorting.c and create the executable file sorting, run `$ make` or `$ make all`. Then run `$ ./sorting` with any combination of the command line arguments a, e, i, s, q, r, n, p, and h. Arguments r, n, and p can take on a value provided by the user (for example, `$ ./sorting -i -n 20 -r 55` runs insertion sort on an array with 20 random elements from a random seed of 55)

Files:
- insert.c
        - Contains implementation for insertion sort
- insert.h
        - Specifies the interface to insert.c
- heap.c 
        - Contains implementation for heap sort
- heap.h
        - Specifies the interface to heap.c
- shell.c
        - Contains implementation for shell sort
- shell.h
        - Specifies the interface to shell.c
- quick.c
        - Contains implementation for quick sort
- quick.h
        - Specifies the interface to quick.c
- sorting.c
        - Contains the main test harness for implemented sorts
- stats.c
        - Contains implementation of the statistics module
- stats.h
        - Specifies the interface to the statistics module.
- set.h
        - Implements and specifies the interface for set usage
- Makefile
        - Contains information for compiling, formatting, and removing .o files and executables
- DESIGN.pdf
        - Contains a detailed explanation of the files, all pseudocode, and notes
- WRITEUP.pdf
        - Contains outputs and graphs comparing the algorithms to each other
- README.md
        - Contains a summary of this assignment

Assistance:
- Watched Eugene’s recorded section on YuJa (learned about the assignment overall and how the algorithms work)
- Watched Chrtisian’s recorded section on YuJa (learned to set up sorting.c and how to use set (insert_set and member_set especially))
- Attended Brian’s section on October 15 (learned about gaps, malloc, and bit masking)
- Learned more about malloc and received tips on how to implement gaps in heap.c from my dad

Citations:
- Assignment document: I followed the pseudocode provided on the assignment document for all sorting algorithms (insertion, heap, shell, and quick on pages 2, 3, 4-5, and 6 respectively)

There are no known bugs/errors according to scan-build, and the program outputs the correct content and format in comparison to the example sorting executable file under the resources repository.
