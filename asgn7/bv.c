#include "bv.h"
#include <stdio.h>

BitVector *bv_create(uint32_t length);

void bv_delete(BitVector **bv);

uint32_t bv_length(BitVector *bv);

bool bv_set_bit(BitVector *bv, uint32_t i);

bool bv_clr_bit(BitVector *bv, uint32_t i);

bool bv_get_bit(BitVector *bv, uint32_t i);

void bv_print(BitVector *bv);
