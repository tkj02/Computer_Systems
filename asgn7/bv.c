#include "bv.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(length);
    if (bv == NULL) {
        return NULL;
    }
    if (bv) {
        bv->length = length;
        for (uint32_t i = 0; i < length; i++) {
            bv->vector[i] = 0;
        }
    }
    return bv;
}

void bv_delete(BitVector **bv) {
    free(*bv);
    *bv = NULL;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i >= bv->length) {
        return false;
    }
    uint32_t byte_index = i / 8;
    uint32_t bit_index = i % 8;
    uint8_t mask = 1 << bit_index;
    bv->vector[byte_index] |= mask;
    return true;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i >= bv->length) {
        return false;
    }
    uint32_t byte_index = i / 8;
    uint32_t bit_index = i % 8;
    uint8_t mask = 1 << bit_index;
    bv->vector[byte_index] &= (~mask);
    return true;
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i >= bv->length) {
        return false;
    }
    uint32_t byte_index = i / 8;
    uint32_t bit_index = i % 8;
    uint8_t mask = 1 << bit_index;
    if (bv->vector[byte_index] & mask) {
        return true;
    }
    return false;
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i++) {
        if (bv->vector[i]) {
            printf("%d\n", 1);
        }
        printf("%d\n", 0);
    }
}
