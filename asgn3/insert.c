#include "stats.h"

#include <stdio.h>

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (int i = 0; i < n; i++) {
        int j = i;
        int temp = A[i];
        while (j > 0 && temp < A[j - 1]) {
            A[j] = A[j - 1];
            j -= 1;
        }
        A[j] = temp;
    }
}
