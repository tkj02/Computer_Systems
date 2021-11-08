#include "pq.h"
#include "code.h"
#include "node.h"
#include "stack.h"
#include "io.h"
#include "huffman.h"
#include "header.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

// Prototype of decode function
bool decode(Node *root, int infile, int outfile);

// Main function
int main(int argc, char **argv) {

    // Initializes necessary structs/variables
    // fileStat is for reading/writing
    // hdr is for header data
    // fi and fout = infile and outfile
    // in_size = infile size and out_size = outfile size
    struct stat fileStat;
    Header hdr;
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
                printf("file open failed for %s\n", optarg);
                if (fout != 1) {
                    close(fout);
                }
                return -1;
            }
            break;

        // Opens outfile
        case 'o':
            fout = open(optarg, O_RDWR | O_CREAT);
            if (fout == -1) {
                printf("file open for write failed for %s\n", optarg);
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

    // Reads bytes from infile given header
    read_bytes(fi, (uint8_t *) &hdr, sizeof(Header));

    // Creates buffer and reads bytes again given size of tree
    uint8_t *buffer = malloc(hdr.tree_size);
    read_bytes(fi, (uint8_t *) buffer, hdr.tree_size);

    // Creates root of Huffman tree
    Node *huffroot;

    // Stores rebuild_tree boolen in root
    huffroot = rebuild_tree(hdr.tree_size, buffer);

    for (uint64_t i = 0; i < hdr.file_size; i++) {
        if (decode(huffroot, fi, fout) == false) {
            break;
        }
    }

    // Sets permission of outfile
    fstat(fout, &fileStat);
    out_size = fileStat.st_size;

    // Checks -v flag
    if (v_flag) {
        temp = 100.0 * (1.0 - ((float) in_size / (float) out_size));
        printf("Compressed file size: %lu\nDecompressed file size: %lu\nSpace saving: %f\n",
            in_size, out_size, temp);
    }

    // Frees memory
    delete_tree(&huffroot);
    node_delete(&huffroot);
    free(buffer);

    // Closes infile and outfile
    if (fi != 0) {
        close(fi);
    }
    if (fout != 1) {
        close(fout);
    }

    return 0;
}

// decode function
// Recursively calls itself until both children of root
// node is null (meaning we have reached the end of the tree)
bool decode(Node *root, int infile, int outfile) {
    if (root == NULL) {
        return false;
    }
    if (root->left == NULL && root->right == NULL) {
        write(outfile, &root->symbol, 1);
        return true;
    }
    uint8_t bit;
    bool flag;
    flag = read_bit(infile, &bit);
    if (flag == false) {
        return false;
    }
    if (bit == 0) {
        return decode(root->left, infile, outfile);
    } else {
        return decode(root->right, infile, outfile);
    }
    return false;
}
