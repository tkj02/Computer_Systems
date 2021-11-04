#include "code.h"
#include "defines.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    uint64_t current_bytes_read = 0;
    while (read(infile, buf + bytes_read, nbytes - bytes_read > 0)) {
        bytes_read += current_bytes_read;
        if (bytes_read == (uint64_t) nbytes) {
            break;
        }
    }
    return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    uint64_t current_bytes_written = 0;
    while (write(outfile, buf + bytes_written, nbytes - bytes_written > 0)) {
        bytes_written += current_bytes_written;
        if (bytes_written == (uint64_t) nbytes) {
            break;
        }
    }
    return bytes_written;
}

bool read_bit(int infile, uint8_t *bit) {
    static uint8_t buffer_array[BLOCK] = {0};
    static uint32_t bit_top = 0;
    static uint32_t bit_buffer_size = 0;
    if (bit_top == 0) {
        bit_buffer_size = read_bytes(infile, buffer_array, BLOCK);
        if (bit_buffer_size == 0) {
            return false;
        }
    }
    *bit = buffer_array[bit_buffer_size];
    bit_top++;
    if (bit_top == bit_buffer_size * 8) {
        bit_top = 0;
    }
    return true;
}

void write_code(int outfile, Code *c) {
}

void flush_codes(int outfile) {
}
