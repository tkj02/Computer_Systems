#include "stats.h"

#include <math.h>
#include <stdio.h>

// Shell Algorithm Implementation
// Creates gap that is then reduced until gap is one
// Very similar to Insertion Algorithm Implementation
// Follows assignment document pseudocode

// Creates static variables for gap implementation
static uint32_t i = 0;

static uint32_t gap_array[32];

uint32_t array_size;

void gaps(uint32_t n) {
    uint32_t range = (uint32_t)(log(3 + 2 * n) / log(3));
    uint32_t index = 0;
    for (uint32_t i = range; i > 0; --i) {
        gap_array[index++] = (uint32_t)((pow(3, i) - 1) / 2);
    }
    array_size = range;
}

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    gaps(n);
    for (uint32_t ii = 0; ii < array_size; ii++) {
        uint32_t gap = gap_array[ii];
        for (uint32_t i = gap; i < n; i++) {
            uint32_t j = i;
            uint32_t temp = move(stats, A[i]);
            while (j >= gap && cmp(stats, temp, A[j - gap]) < 0) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(stats, temp);
        }
    }
}
