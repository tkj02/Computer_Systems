#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "hst:f:"

int main(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n   A word filtering program for the GPRSC.\n");
            printf("   Filters out and reports bad words parsed from stdin.\n\n");
            printf("USAGE\n   ./banhammer [-hs] [-t size] [-f size]\n\n");
            printf("OPTIONS\n");
            printf("  -h         Program usage and help.\n");
            printf("  -s         Print program statistics.\n");
            printf("  -t size    Specify hash table size (default: 10000).\n");
            printf("  -f size    Specify Bloom filter size (default: 2^20).\n");
            break;
        case 's': break;
        case 't': break;
        case 'f': break;
        }
    }
    return 0;
}
