#include "set.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "aeisqrnph:"

int main(int argc, char **argv) {
    int opt = 0;
    //s = empty_set(); //set to track inputs

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            // add a to set - all sorts
            break;
        case 'e':
            // add e to set - heap
            break;
        case 'i':
            // add i to set - insertion
            break;
        case 's':
            // add s to set - shell
            break;
        case 'q':
            // add q to set - quick
            break;
        case 'r':
            // add r to set - random seed
            break;
        case 'n':
            // add n to set - array size
            break;
        case 'p':
            // add p to set - # of elementst
            break;
        case 'h':
            // add h to set - program usage
            break;
        }
    }
}
