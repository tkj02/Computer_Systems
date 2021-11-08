#include "pq.h"
#include "code.h"
#include "node.h"
#include "stack.h"
#include "io.h"
#include "huffman.h"
#include "defines.h"
#include "header.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define OPTIONS "hi:o:v"

// Protoypes of functions that will be used
// create_hist and get_unique_count are under main()
// decode is under huffman.c
int create_hist(int fd);
int get_unique_count();
bool decode(Node *root, int infile, int outfile);

// Global variables
// Initializes histogram and code table
uint64_t g_hist[ALPHABET];
Code g_table[ALPHABET];

// Main function
int main(int argc, char **argv) {

    // Creates necessary structs/variables
    // fileStat is for reading/writing
    // hdr is for header data
    struct stat fileStat;
    Header hdr;

    // Initializes necessary structs/variables
    // fi and fout = infile and outfile
    // in_size = infile size and out_size = outfile size
    int opt = 0;
    int fi = 0;
    int fout = 1;
    uint64_t in_size;
    uint64_t out_size = 0;
    float temp;
    bool v_flag = false;

    // Parses through command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {

        // Prints help message
        case 'h':
            printf("SYNOPSIS\n  A Huffman encoder.\n  Compresses a file using the Huffman coding "
                   "algorithm.\n\n");
            printf("USAGE\n  ./encode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -v             Print compression statistics.\n");
            printf("  -i infile      Input file to compress.\n");
            printf("  -o outfile     Output of compressed data.\n");
            break;

        // Prints compression statistics
        case 'v': v_flag = true; break;

        // Opens infile
        case 'i':
            fi = open(optarg, O_RDONLY);
            if (fi == -1) {
                printf("file open for reading failed\n");
                if (fout != 1) {
                    close(fout);
                }
                return -1;
            }
            break;

        // Opens outfile
        // Sets permission of infile and outfile
        // in_size stores size of uncompressed file (infile)
        case 'o':
            fout = open(optarg, O_RDWR | O_CREAT);
            if (fout == -1) {
                printf("file open for write failed for\n");
                if (fi != 0) {
                    close(fi);
                }
                return -1;
            }
            fstat(fi, &fileStat);
            in_size = fileStat.st_size;
            fchmod(fout, fileStat.st_mode);
            break;
        }
    }

    // Creates histogram and sets all values to zero
    create_hist(fi);

    // Creates root node of Huffman tree based on histogram
    Node *hroot = build_tree(g_hist);
    if (hroot == NULL) {
        printf("error failed huff tree\n");
        return -1;
    }

    // Creates codes for each node
    build_codes(hroot, g_table);

    // Opens infile to read again
    lseek(fi, 0, SEEK_SET);

    // Assignment for header members
    hdr.magic = MAGIC;
    hdr.permissions = fileStat.st_mode;
    hdr.tree_size = (3 * get_unique_count()) - 1;
    hdr.file_size = fileStat.st_size;

    // Writes bytes of header to outfile
    write_bytes(fout, (uint8_t *) &hdr, sizeof(Header));

    // Dumps the tree
    dump_tree(fout, hroot);

    // Creates buffer for writing codes to outfile
    uint8_t *buffer = malloc(BLOCK);
    if (buffer == NULL) {
        printf("error allocating\n");
        return -1;
    }

    // Writes codes to outfile until the end of infile
    while (1) {
        uint32_t return_len = read(fi, buffer, BLOCK);
        if (return_len < 1) {
            break;
        }
        for (uint32_t i = 0; i < return_len; i++) {
            write_code(fout, &g_table[buffer[i]]);
        }
    }

    // Flushes remaining codes to outfile
    flush_codes(fout);

    // Sets permission of outfile
    fstat(fout, &fileStat);

    // Stores size of compressed file (outfile)
    out_size = fileStat.st_size;

    // Checks -v case
    if (v_flag) {
        temp = 100.0 * (1.0 - ((float) out_size / (float) in_size));
        printf("Uncompressed file size: %lu\nCompressed file size: %lu\nSpace saving: %f\n",
            in_size, out_size, temp);
    }

    // Frees memory
    free(buffer);
    delete_tree(&hroot);

    // Closes files
    if (fout != 1) {
        close(fout);
    }
    if (fi != 0) {
        close(fi);
    }

    return 0;
}

// create_hist function
// Creates the histogram for tracking frequency
int create_hist(int fd) {
    char *buffer = malloc(BLOCK);
    if (buffer == NULL) {
        printf("error allocating\n");
        return -1;
    }

    // Initializes all values to zero
    for (uint32_t i = 0; i < ALPHABET; i++) {
        g_hist[i] = 0;
    }

    // Sets first and last values to 1
    g_hist[0] = 1;
    g_hist[ALPHABET - 1] = 1;

    // Increments histogram by frequency
    while (1) {
        uint32_t return_len = read(fd, buffer, BLOCK);
        if (return_len < 1) {
            break;
        }
        for (uint32_t i = 0; i < return_len; i++) {
            int index = (int) buffer[i];
            g_hist[index]++;
        }
    }

    // Frees memory
    free(buffer);
    return 0;
}

// get_unique_count function
// Gets the number of non-zero symbols in the histogram
// This is used for the header tree_size
int get_unique_count() {
    int unique_count = 0;
    for (int i = 0; i < ALPHABET; i++) {
        if (g_hist[i] == 0) {
            continue;
        }
        unique_count++;
    }
    return unique_count;
}
