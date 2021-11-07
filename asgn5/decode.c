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

bool decode(Node *root, int infile, int outfile);

int main(int argc, char **argv) {
    int opt = 0;
    int fi = 0;
    int fout = 1;
    struct stat fileStat;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
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
        case 'v': break;
        case 'i':
            fi = open(optarg, O_RDONLY);
            if (fi == -1) {
                printf("file open failed for %s\n", optarg);
                return -1;
            }
            break;
        case 'o':
            fout = open(optarg, O_RDWR | O_CREAT);
            if (fout == -1) {
                printf("file open for write failed for %s\n", optarg);
                return -1;
            }
            fstat(fi, &fileStat);
            fchmod(fout, fileStat.st_mode);
            break;
        }
    }

    Header hdr;
    read_bytes(fi, (uint8_t *) &hdr, sizeof(Header));
    printf("magic %04x permissions %02x tree size %d file size %lu\n", hdr.magic, hdr.permissions,
        hdr.tree_size, hdr.file_size);

    char *buffer = malloc(hdr.tree_size);
    read_bytes(fi, (uint8_t *) buffer, hdr.tree_size);

    Stack *stack = stack_create(32);
    for (int i = 0; i < hdr.tree_size; i++) {
        if (buffer[i] == 'L') {
            Node *n = node_create(buffer[i + 1], 0);
            stack_push(stack, n);
            i++;
        } else {
            if (buffer[i] == 'I') {
                Node *left;
                Node *right;
                stack_pop(stack, &right);
                stack_pop(stack, &left);
                Node *parent = node_join(left, right);
                stack_push(stack, parent);
            } else {
                printf("error invalid entry in tree\n");
            }
        }
    }

    Node *huffroot;
    stack_pop(stack, &huffroot);
    free(buffer);
    stack_delete(&stack);

#if 1

    int call_count = 0;
    while (1) {
        if (decode(huffroot, fi, fout) == false) {
            break;
        }
        call_count++;
        //printf("call count %d\n", call_count);
    }
    return 0;
}
#endif
