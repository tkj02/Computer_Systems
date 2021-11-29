#include "salts.h"
#include "bf.h"
#include <stdio.h>
#include <stdlib.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = malloc(size);
    if (bf == NULL) {
        return bf;
    }
    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;
    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;
    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;
    bf->filter = bv_create(size);
    return bf;
}

void bf_delete(BloomFilter **bf) {
    free(bf);
    bf = NULL;
}

#if 0
uint32_t bf_size(BloomFilter *bf){

}

void bf_insert(BloomFilter *bf, char *oldspeak){

}

bool bf_probe(BloomFilter *bf, char *oldspeak){

}

uint32_t bf_count(BloomFilter *bf){

}

void bf_print(BloomFilter *bf){

}
#endif
