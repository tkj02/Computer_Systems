#include "stats.h"

#include <math.h>
#include <stdio.h>

static uint32_t i = 0;

uint32_t gaps(uint32_t n) {
    if (i <= 0) {
        i = (uint32_t)(log(3 + 2 * n) / log(3));
    } else {
        --i;
    }
    return (uint32_t)((pow(3, i) - 1) / 2);
}

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t iters = (log(3 + 2 * n) / log(3));
    for (uint32_t g = 0; g < iters; g++) {
        uint32_t gap = gaps(n);
        for (uint32_t i = gap; i < n; i++) {
            uint32_t j = i;
            uint32_t temp = move(stats, A[i]);
            while (j >= g && temp < A[j - g]) {
                A[j] = move(stats, A[j - g]);
                j -= g;
            }
            A[j] = move(stats, temp);
        }
    }
}
