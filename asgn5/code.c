#include "code.h"
#include "defines.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Using Code struct from code.h
// Has uint32_t top and uint8_t bits[MAX_CODE_SIZE]

Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint8_t i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0;
    }
    return c;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    }
    return false;
}

bool code_set_bit(Code *c, uint32_t i) {
    if (i >= ALPHABET) {
        return false;
    }
    int byte_index = i / 8;
    int bit_index = i % 8;
    uint8_t mask = 1 << bit_index;
    c->bits[byte_index] = c->bits[byte_index] | mask;
    return true;
}

bool code_clr_bit(Code *c, uint32_t i) {
    if (i >= ALPHABET) {
        return false;
    }
    int byte_index = i / 8;
    int bit_index = i % 8;
    uint8_t mask = 1 << bit_index;
    c->bits[byte_index] = c->bits[byte_index] & (~mask);
    return true;
}

bool code_get_bit(Code *c, uint32_t i) {
    if (i >= ALPHABET) {
        return false;
    }
    int byte_index = i / 8;
    int bit_index = i % 8;
    uint8_t mask = 1 << bit_index;
    if (c->bits[byte_index] & mask) {
        return true;
    }
    return false;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    int byte_index = c->top / 8;
    int bit_index = c->top % 8;
    uint8_t mask = 1 << bit_index;
    if (bit == 0) {
        c->bits[byte_index] &= ~mask;
    } else {
        c->bits[byte_index] |= mask;
    }
    c->top++;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    --c->top;
    int byte_index = c->top / 8;
    int bit_index = c->top % 8;
    uint8_t mask = 1 << bit_index;
    if ((c->bits[byte_index] & mask) != 0) {
        *bit = 1;
    } else {
        *bit = 0;
    }
    return true;
}

void code_print(Code *c) {
    for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) {
        printf("bit at index #%u: %hu\n", i, c->bits[i]);
    }
}
