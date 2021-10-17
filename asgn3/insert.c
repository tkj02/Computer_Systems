#include "stats.h"

#include <stdio.h>

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        int temp = move(stats, A[i]);
        while (j > 0 && cmp(stats, temp, A[j - 1]) < 0) {
            A[j] = move(stats, A[j - 1]);
            j -= 1;
        }
        A[j] = move(stats, temp);
    }
}
