#include "code.h"
#include "defines.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int current_bytes_read = 0;
    int bytes_read = 0;
    while (bytes_read < nbytes) {
        current_bytes_read = read(infile, buf + bytes_read, nbytes - bytes_read);
        if (current_bytes_read < 1) {
            break;
        }
        bytes_read += current_bytes_read;
    }
    return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int current_bytes_written = 0;
    int bytes_written = 0;
    while (bytes_written < nbytes) {
        current_bytes_written = write(outfile, buf + bytes_written, nbytes - bytes_written);
        if (current_bytes_written < 1) {
            break;
        }
        bytes_written += current_bytes_written;
    }
    return bytes_written;
}

bool read_bit(int infile, uint8_t *bit) {
    static uint8_t buffer_array[BLOCK] = { 0 };
    static uint32_t index = 0;
    static uint32_t end = -1;
    if (index == 0) {
        uint32_t bits_read = read_bytes(infile, buffer_array, BLOCK);
        //printf("bits read %u\n", bits_read);
        if (bits_read < BLOCK) {
            end = bits_read * 8 + 1;
        }
        if (bits_read <= 0) {
            return false;
        }
    }
    int byte_index = index / 8;
    int bit_index = index % 8;
    uint8_t temp = buffer_array[byte_index];
    uint8_t mask = 1 << bit_index;
    //printf("bi %d byi %d temp %d \n", bit_index, byte_index, temp);
    if ((temp & mask) != 0) {
        *bit = 1;
    } else {
        *bit = 0;
    }
    index++;
    if (index == BLOCK * 8) {
        index = 0;
    }
    if (index == end) {
        return false;
    }
    return true;
}

static uint8_t buffer[BLOCK] = { 0 };
static uint32_t index = 0;

void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); i++) {
        uint32_t bit = code_get_bit(c, i);
        int byte_index = index / 8;
        int bit_index = index % 8;
        uint8_t mask = 1 << bit_index;
        buffer[byte_index] = buffer[byte_index] & (~mask);

        if (bit == 1) {
            buffer[byte_index] = buffer[byte_index] | mask;
        }
        index++;
        if (index == BLOCK * 8) {
            write_bytes(outfile, buffer, BLOCK);
            index = 0;
        }
    }
}

void flush_codes(int outfile) {
    if (index > 0) {
        write_bytes(outfile, buffer, (index + 7) / 8);
    }
    index = 0;
}
