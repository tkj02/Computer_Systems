#include "node.h"
#include "bv.h"
#include "bst.h"
#include "bf.h"
#include "ht.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "hst:f:"

int main(int argc, char **argv) {

#if 0
    uint32_t height;
    uint32_t size;
    Node *root = bst_create();
    height = bst_height(root);
    size = bst_size(root);
    printf("height = %u   size = %u\n", height, size);
    bst_print(root);
    root = bst_insert(root, "mmmm", "new");
    bst_insert(root, "aaaa", "another1");
    bst_insert(root, "ooo", "cat");
    bst_insert(root, "pp", NULL);

    height = bst_height(root);
    size = bst_size(root);
    printf("height = %u   size = %u\n", height, size);
    bst_print(root);

    Node *find = bst_create();
    find = bst_find(root, "ooo");
    bst_print(find);

    return 0;
#endif

    int opt = 0;
    uint32_t ht_size = 1 << 16;
    uint32_t bf_size = 1 << 20;
    bool stat_flag = false;

    // Parses through command line arguments
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n  A word filtering program for the GPRSC.\n");
            printf("  Filters out and reports bad words parsed from stdin.\n\n");
            printf("USAGE\n  ./banhammer [-hs] [-t size] [-f size]\n\n");
            printf("OPTIONS\n");
            printf("  -h           Program usage and help.\n");
            printf("  -s           Print program statistics.\n");
            printf("  -t size      Specify hash table size (default: 10000).\n");
            printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
            break;
        case 's': stat_flag = true; break;
        case 't': ht_size = atoi(optarg); break;
        case 'f': bf_size = atoi(optarg); break;
        }
    }

    // Initializes bloom filter
    BloomFilter *bf = bf_create(bf_size);

    // Initializes hash table
    HashTable *ht = ht_create(ht_size);

    // Checks if -s was enabled
    if (stat_flag) {
        //calculate statistics and print
    }

    // Frees memory
    bf_delete(&bf);
    ht_delete(&ht);

    return 0;
}
