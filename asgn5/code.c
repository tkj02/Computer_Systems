#include "code.h"
#include "defines.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Using Code struct from code.h
// Has uint32_t top and uint8_t bits[MAX_CODE_SIZE]

// Creates Code data
// Has top set to zero
// As bits array initialized to zero as well
Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint8_t i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0;
    }
    return c;
}

// Returns the size of the code, or the top
uint32_t code_size(Code *c) {
    return c->top;
}

// Checks that the code isn't empty
bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

// Checks that the code isn't full
bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    }
    return false;
}

// If not out of range, sets code
// Checks that we are setting at the correct
// byte and bit inside the byte by masking with OR
bool code_set_bit(Code *c, uint32_t i) {
    if (i >= ALPHABET) {
        return false;
    }
    int byte_index = i / 8;
    int bit_index = i % 8;
    uint8_t mask = 1 << bit_index;
    c->bits[byte_index] |= mask;
    return true;
}

// If not out of range, clears code
// Checks that we are setting at the correct
// byte and bit inside the byte by masking with AND
bool code_clr_bit(Code *c, uint32_t i) {
    if (i >= ALPHABET) {
        return false;
    }
    int byte_index = i / 8;
    int bit_index = i % 8;
    uint8_t mask = 1 << bit_index;
    c->bits[byte_index] &= (~mask);
    return true;
}

// If not out of range, sets code
// Checks that we are getting at the correct
// byte and bit inside the byte by masking again
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

// If code isn't full, look at the bit and do respective action
// If zero, AND with mask and if one, OR with mask
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

// If code isn't empty, pop bit
// Sets pointer bit to one if AND is not zero
// and sets to zero otherwise
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

// Prints number of bits according to code size
void code_print(Code *c) {
    printf("number of bits: %d\n", code_size(c));
}
