#include "salts.h"
#include "bf.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>

// Creates bloom filter structure
struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    // Allocates memory for bloom filter
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf == NULL) {
        return bf;
    }

    // Sets salt values according to salts.h
    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;
    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;
    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;

    // Sets bit vector size to bloom filter's size
    bf->filter = bv_create(size);

    // Returns bloom filter pointer
    return bf;
}

void bf_delete(BloomFilter **bf) {
    // Frees bit vector memory
    bv_delete(&((*bf)->filter));

    // Frees bloom filter memory
    free(bf);
    *bf = NULL;
}

uint32_t bf_size(BloomFilter *bf) {
    // Returns length of filter bit vector
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    // Gets primary, secondary, and tertiary bits from hashing
    uint32_t p_bit = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t s_bit = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t t_bit = hash(bf->tertiary, oldspeak) % bf_size(bf);

    // Sets corresponding bits of filter to one
    bv_set_bit(bf->filter, p_bit);
    bv_set_bit(bf->filter, s_bit);
    bv_set_bit(bf->filter, t_bit);
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    // Gets primary, secondary, and tertiary bits from hashing
    uint32_t p_bit = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t s_bit = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t t_bit = hash(bf->tertiary, oldspeak) % bf_size(bf);

    // Returns false if any of the corresponding bits in filter are zero
    if (bv_get_bit(bf->filter, p_bit) == false || bv_get_bit(bf->filter, s_bit) == false
        || bv_get_bit(bf->filter, t_bit) == false) {
        return false;
    }

    // Only returns true if all bits are set to one
    return true;
}

uint32_t bf_count(BloomFilter *bf) {
    // Keeps track of number of set bits in filter
    uint32_t counter = 0;

    // Iterates through all indices of filter
    for (uint32_t i = 0; i < bv_length(bf->filter); i++) {

        // If bit at index is one, increments counter by one
        if (bv_get_bit(bf->filter, i)) {
            counter++;
        }
    }

    // Returns final count of set bits
    return counter;
}

void bf_print(BloomFilter *bf) {
    // Iterates through all indices of filter
    for (uint32_t i = 0; i < bv_length(bf->filter); i++) {

        // If bit at index is one, prints one
        if (bv_get_bit(bf->filter, i)) {
            printf("1\n");
        }

        // If bit at index is zero, prints zero
        else {
            printf("0\n");
        }
    }
}
