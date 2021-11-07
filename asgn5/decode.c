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
    uint64_t in_size;
    uint64_t out_size = 0;
    float temp;
    bool v_flag = false;

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
        case 'v': v_flag = true; break;
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

    fstat(fout, &fileStat);
    out_size = fileStat.st_size;

    if (v_flag) {
        temp = 100.0 * (1.0 - ((float) out_size / (float) in_size));
        printf("input size %lu output size %lu space saving %f\n", in_size, out_size, temp);
    }

    int call_count = 0;
    while (1) {
        if (decode(huffroot, fi, fout) == false) {
            break;
        }
        call_count++;
    }
    return 0;
}

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
