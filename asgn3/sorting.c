#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS       "aeisqr:n:p:h"
#define HEAP_BIT      0
#define INSERTION_BIT 1
#define SHELL_BIT     2
#define QUICK_BIT     3
#define RANDOM_BIT    4
#define SIZE_BIT      5
#define HEX_30_BITS   0x3FFFFFFF

// Creates static variables of default values (for -r, -n, and -p)
static uint32_t seed = 13371453;
static uint32_t size = 100;
static uint32_t print_size = 100;

// Creates array of random elements
// ptr = pointer (here and everywhere else)
uint32_t *create_array(uint32_t size, uint32_t seed) {
    uint32_t *ptr;
    ptr = malloc(size * sizeof(uint32_t));
    if (ptr == NULL) {
        return NULL;
    }
    srandom(seed);
    for (uint32_t i = 0; i < size; i++) {
        *(ptr + i) = random() & HEX_30_BITS;
    }
    return ptr;
}

// Creates random elemets (for -a, -e, -i, -s, and -q)
void init_random(uint32_t *ptr, uint32_t size, uint32_t seed) {
    srandom(seed);
    for (uint32_t i = 0; i < size; i++) {
        *(ptr + i) = random() & HEX_30_BITS;
    }
}

// Prints statistics (and elements if asked) for each sort
void print_result(Stats *stat_ptr, char *label, uint32_t *data_ptr) {
    printf("%s, %d"
           " elements,",
        label, size);
    printf(" %lu"
           " moves,",
        stat_ptr->moves);
    printf(" %lu"
           " compares\n",
        stat_ptr->compares);
    if (print_size > size) {
        print_size = size;
    }
    for (uint32_t i = 0; i < print_size; i++) {
        if (i > 0 && i % 5 == 0) {
            printf("\n");
        }
        printf("%13" PRIu32, *(data_ptr + i));
    }
    printf("\n");
}

// Main function
// Makes use of set.h's inserts and members
// Makes use of create_array, init_random, and print_results
int main(int argc, char **argv) {
    Stats insert_stats;
    Stats shell_stats;
    Stats heap_stats;
    Stats quick_stats;
    int opt = 0;
    Set s = empty_set();
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            // all sorts
            s = insert_set(HEAP_BIT, s);
            s = insert_set(INSERTION_BIT, s);
            s = insert_set(SHELL_BIT, s);
            s = insert_set(QUICK_BIT, s);
            break;
        case 'e':
            // heap
            s = insert_set(HEAP_BIT, s);
            break;
        case 'i':
            // insertion
            s = insert_set(INSERTION_BIT, s);
            break;
        case 's':
            // shell
            s = insert_set(SHELL_BIT, s);
            break;
        case 'q':
            // quick
            s = insert_set(QUICK_BIT, s);
            break;
        case 'r':
            // random seed
            seed = atoi(optarg);
            break;
        case 'n':
            // array size
            size = atoi(optarg);
            break;
        case 'p':
            // # of elements
            print_size = atoi(optarg);
            break;
        case 'h':
            // program usage
            printf("SYNOPSIS\n   A collection of comparison-based sorting algorithms.\n\n");
            printf("USAGE\n   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
            printf("OPTIONS\n");
            printf("   -h              display program help and usage\n");
            printf("   -a              enable all sorts.\n");
            printf("   -e              enable Heap Sort.\n");
            printf("   -i              enable Insertion Sort.\n");
            printf("   -s              enable Shell Sort.\n");
            printf("   -q              enable Quick Sort.\n");
            printf("   -n length       specify number of array elements (default: 100).\n");
            printf("   -p elements     specify number of elements to print (default: 100).\n");
            printf("   -r seed         specify random seed (default: 13371453).\n");
            break;
        }
    }

    uint32_t *test_pattern;

#if 1
    test_pattern = malloc(size * sizeof(uint32_t));
    if (test_pattern == NULL) {
        return -1;
    }
#else
    test_pattern = create_array(size, seed);
    if (test_pattern == NULL) {
        return -1;
    }
#endif

    if (member_set(HEAP_BIT, s)) {
        init_random(test_pattern, size, seed);
        reset(&heap_stats);
        heap_sort(&heap_stats, test_pattern, size);
        print_result(&heap_stats, "Heap Sort", test_pattern);
    }

    if (member_set(SHELL_BIT, s)) {
        init_random(test_pattern, size, seed);
        reset(&shell_stats);
        shell_sort(&shell_stats, test_pattern, size);
        print_result(&shell_stats, "Shell Sort", test_pattern);
    }

    if (member_set(INSERTION_BIT, s)) {
        init_random(test_pattern, size, seed);
        reset(&insert_stats);
        insertion_sort(&insert_stats, test_pattern, size);
        print_result(&insert_stats, "Insertion Sort", test_pattern);
    }

    if (member_set(QUICK_BIT, s)) {
        init_random(test_pattern, size, seed);
        reset(&quick_stats);
        quick_sort(&quick_stats, test_pattern, size);
        print_result(&quick_stats, "Quick Sort", test_pattern);
    }

    free(test_pattern);
    return 0;
}
