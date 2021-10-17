#include "stats.h"

#include <stdio.h>

uint32_t partition(uint32_t *A, uint32_t low, uint32_t high) {
    uint32_t i = low - 1;
    for (uint32_t j = low; j < high; j++) {
        if (A[j - 1] < A[high - 1]) {
            i++;
            uint32_t temp = A[i - 1];
            A[i - 1] = A[j - 1];
            A[j - 1] = temp;
        }
    }
    uint32_t temp2 = A[i];
    A[i] = A[high - 1];
    A[high - 1] = temp2;
    return i + 1;
}

void quick_sorter(uint32_t *A, uint32_t low, uint32_t high) {
    if (low < high) {
        uint32_t p = partition(A, low, high);
        quick_sorter(A, low, p - 1);
        quick_sorter(A, p + 1, high);
    }
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(A, 1, n);
}
