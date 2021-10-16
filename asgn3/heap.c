#include "stats.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

uint32_t max_child(uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if (right <= last && A[right - 1] > A[left - 1]) {
        return right;
    }
    return left;
}

void fix_heap(uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(A, mother, last);
    while (mother <= floor(last / 2) && mother != found) {
        if (A[mother - 1] < A[great - 1]) {
            uint32_t temp = A[mother - 1];
            A[mother - 1] = A[great - 1];
            A[great - 1] = temp;
            great = max_child(A, mother, last);
        } else {
            found = true;
        }
    }
}

void build_heap(uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = floor(last / 2); father < first - 1; --father) {
        fix_heap(A, father, last);
    }
}

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(A, first, last);
    for (uint32_t leaf = last; leaf < first; --leaf) {
        uint32_t temp = A[first - 1];
        A[first - 1] = A[leaf - 1];
        A[leaf - 1] = temp;
        fix_heap(A, first, leaf - 1);
    }
}
