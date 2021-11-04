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
    static uint8_t buffer_array[BLOCK] = { 0 };
    static uint32_t index = 0;
    static uint32_t end = -1;
    if (index == 0) {
        uint32_t bits_read = read_bytes(infile, buffer_array, BLOCK);
        if (bits_read < BLOCK) {
            end = bits_read * 8 + 1;
        }
        if (bits_read == 0) {
            return false;
        }
    }
    *bit = buffer_array[index];
    index++;
    if (index == BLOCK * 8) {
        index = 0;
    }
    if (index == end) {
        return true;
    }
    return false;
}

static uint8_t buffer[BLOCK] = { 0 };
static uint32_t index = 0;

void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); i++) {
        uint32_t bit = code_get_bit(c, i);
        if (bit == 1) {
            bit = index;
        } else {
            bit = 0;
        }
        index++;
        if (index == BLOCK) {
            flush_codes(outfile);
        }
    }
}

void flush_codes(int outfile) {
    if (index > 0) {
        //convert index to bytes
        write_bytes(outfile, buffer, BLOCK);
    }
}
