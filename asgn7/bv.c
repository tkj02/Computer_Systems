#include "bv.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Creates bit vector structure
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    // Allocates memory for bit vector
    BitVector *bv = (BitVector *) malloc(length * sizeof(BitVector));
    if (bv == NULL) {
        return NULL;
    }

    // Sets bit vector length
    bv->length = length;

    // Sets all values of bit vector to zero
    for (uint32_t i = 0; i < bv->length; i++) {
        bv->vector[i] = 0;
    }

    // Returns bit vector pointer
    return bv;
}

void bv_delete(BitVector **bv) {
    // Frees bit vector memory
    free(*bv);
    *bv = NULL;
}

uint32_t bv_length(BitVector *bv) {
    // Returns bit vector length
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    // Returns false if i is out of range
    if (i >= bv->length) {
        return false;
    }

    // Keeps track of byte
    uint32_t byte_index = i / 8;

    // Keepts track of bit of byte
    uint32_t bit_index = i % 8;

    // Creates a mask for logical operation
    uint8_t mask = 1 << bit_index;

    // Sets bit at byte of bit vector
    // If it is zero prior to masking, it will become one
    // If it is one prior to masking, it remains as one
    bv->vector[byte_index] |= mask;

    return true;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    // Returns false if i is out of range
    if (i >= bv->length) {
        return false;
    }

    // Keeps track of byte
    uint32_t byte_index = i / 8;

    // Keepts track of bit of byte
    uint32_t bit_index = i % 8;

    // Creates a mask for logical operation
    uint8_t mask = 1 << bit_index;

    // Clears bit at byte of bit vector
    // If it it zero prior to masking, it remains as zero
    // If it is one prior to masking, it will become zero
    bv->vector[byte_index] &= (~mask);

    return true;
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    // Returns false if i is out of range
    if (i >= bv->length) {
        return false;
    }

    // Keeps track of byte
    uint32_t byte_index = i / 8;

    // Keepts track of bit of byte
    uint32_t bit_index = i % 8;

    // Creates a mask for logical operation
    uint8_t mask = 1 << bit_index;

    // Returns true if bit at byte of bit vector is one
    if (bv->vector[byte_index] & mask) {
        return true;
    }

    // Returns false if bit at byte of bit vector is zero
    return false;
}

void bv_print(BitVector *bv) {
    // Prints zero or one to corresponding bit vector value
    for (uint32_t i = 0; i < bv->length; i++) {
        if (bv->vector[i]) {
            printf("%d\n", 1);
        }
        printf("%d\n", 0);
    }
}
