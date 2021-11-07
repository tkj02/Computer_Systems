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

#define OPTIONS "hi:o:v"

bool decode(Node *root, int infile, int outfile);

uint64_t g_hist[ALPHABET];
Code g_table[ALPHABET];

int create_hist(int fd) {
    char *buffer = malloc(BLOCK);
    if (buffer == NULL) {
        printf("error allocating\n");
        return -1;
    }
    for (uint32_t i = 0; i < ALPHABET; i++) {
        g_hist[i] = 0;
    }
    g_hist[0] = 1;
    g_hist[ALPHABET - 1] = 1;
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
    free(buffer);
    return 0;
}

int main(int argc, char **argv) {

#if 1
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        printf("error not found\n");
        return -1;
    }
    PriorityQueue *pq = pq_create(ALPHABET);
    create_hist(fd);
    for (int i = 0; i < 256; i++) {
        if (g_hist[i] == 0) {
            continue;
        }
        printf("%3d %lu\n", i, g_hist[i]);
        Node *node = node_create(i, g_hist[i]);
        enqueue(pq, node);
    }
    Node *hroot = build_tree(g_hist);
    if (hroot == NULL) {
        printf("error failed huff tree\n");
        return -1;
    }
    build_codes(hroot, g_table);
    for (int i = 0; i < 256; i++) {
        if (code_size(&g_table[i]) == 0) {
            continue;
        }
        printf("symbol %02x (%c) CodeCount: %d freq: %lu\n", i, (i > ' ' && i < 128) ? i : ' ',
            code_size(&g_table[i]), g_hist[i]);
        // 	code_print(&g_table[i]);
    }
    close(fd);
    fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        printf("error not found\n");
        return -1;
    }
    int fw = open("test.out", O_RDWR | O_CREAT);
    if (fw == -1) {
        printf("error write file open\n");
        return -1;
    }
    uint8_t *buffer = malloc(BLOCK);
    if (buffer == NULL) {
        printf("error allocating\n");
        return -1;
    }
    while (1) {
        uint32_t return_len = read(fd, buffer, BLOCK);
        if (return_len < 1) {
            break;
        }
        for (uint32_t i = 0; i < return_len; i++) {
            write_code(fw, &g_table[buffer[i]]);
        }
    }
    flush_codes(fw);
    free(buffer);
    close(fw);
    close(fd);
    fd = open("test.out", O_RDONLY);
    if (fd == -1) {
        printf("error no test.out for decode\n");
        return -1;
    }
    int bit_count = 0;
    uint8_t tbit;
    while(1){
    	if (read_bit(fd, &tbit) == false){
		break;
	}
	bit_count++;
    }
    printf("%d", bit_count);
    return 0;
    fw = open("decode.out", O_RDWR | O_CREAT);
    if (fw == -1) {
        printf("error decode file open\n");
        return -1;
    }
    while(1){
	    if(decode(hroot, fd, fw) == false){
	    	break;
	    }
    }
    close(fd);
    close(fw);

#if 0
    int q_count = pq_size(pq);

    for (int i = 0; i < q_count; i++) {
        Node *node;
        bool stat = dequeue(pq, &node);
        if (stat == false) {
            printf("failed\n");
        }
        printf(" sorted %3d %lu\n", node->symbol, node->frequency);
    }
#endif

    return 0;

    uint8_t bit;
    int count = 0;
    Code c = code_init();
    while (read_bit(fd, &bit)) {
        if (count % 8 == 0) {
            printf("\n");
        }
        count++;
        printf("%d %x\n", count, bit);
        if (count > 100) {
            break;
        }
        code_push_bit(&c, bit);
    }
    uint32_t size = code_size(&c);
    printf("%u\n", size);
    for (uint32_t i = 0; i < size + 5; i++) {
        if (code_pop_bit(&c, &bit) == false) {
            printf("%d error\n", i);
        }
        printf("%d bit: %d\n", i, bit);
    }
    return 0;

#endif

    int opt = 0;
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
        case 'i': break;
        case 'o': break;
        }
    }
}

// read infile
//	compute frequency of each symbol
//	make histogram
// make tree with histogram
//	use pq
// make code table
// 	index of table represent symbol
// 	value at index represents symbol's code
// 	use stack of bits and traverse tree
// write tree to outfile
// 	use dump_tree()
// write code of each symbol to outfile
// 	use write_code()
// flush remaining code
// 	use flush_codes()
// close infile and outfile
