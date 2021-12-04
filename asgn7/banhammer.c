#include "node.h"
#include "bv.h"
#include "bst.h"
#include "bf.h"
#include "ht.h"
#include "messages.h"
#include "parser.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS       "hst:f:"
#define MAXLEN        1024
#define BADSPEAK_FILE "badspeak.txt"
#define NEWSPEAK_FILE "newspeak.txt"
//#define WORD "([a-zA-Z0-9]+-)+[a-z]+"
#define WORD "[a-zA-Z0-9\'_-]+"

// For testing bf_probe
void test_bf(BloomFilter *bf, char *old) {
    bool flag = bf_probe(bf, old);
    if (flag == true) {
        printf("%s is in bf\n", old);
    } else {
        printf("%s is not in bf\n", old);
    }
}

void print_file(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("error opening %s\n", filename);
        return;
    }
    while (1) {
        // Breaks if EOF reached
        char rd_buffer[256];
        if (fgets(rd_buffer, 256, fp) == NULL) {
            break;
        }

        printf("%s", rd_buffer);
    }
}

void create_report(BloomFilter *bf, HashTable *ht) {
    FILE *badfile;
    FILE *rightfile;

    regex_t re;

    if (regcomp(&re, WORD, REG_EXTENDED)) {
        printf("failed to compile\n");
    }

    char *word = NULL;

    badfile = fopen("badfile.txt", "w");
    if (badfile == NULL) {
        printf("error openining file badfile.txt\n");
        return;
    }

    rightfile = fopen("rightfile.txt", "w");
    if (rightfile == NULL) {
        printf("error openining file rightfile.txt\n");
        return;
    }

    int bad_count = 0;
    int right_count = 0;
    while ((word = next_word(stdin, &re)) != NULL) {
        printf("word return %s\n", word);
        if (bf_probe(bf, word) == false) {
            continue;
        }
        Node *ht_node = ht_lookup(ht, word);
        if (ht_node == NULL) {
            continue;
        }
        printf("found guilty\n");
        node_print(ht_node);

        if (ht_node->newspeak == NULL) {
            bad_count++;
            fprintf(badfile, "%s\n", ht_node->oldspeak);
        } else {
            right_count++;
            fprintf(rightfile, "%s -> %s\n", ht_node->oldspeak, ht_node->newspeak);
        }
    }

    printf("closing file\n");
    fclose(badfile);
    fclose(rightfile);

    //printf("bad %d   right %d\n", bad_count, right_count);

    if (bad_count != 0 && right_count != 0) {
        printf("%s", mixspeak_message);
        print_file("badfile.txt");
        print_file("rightfile.txt");
    }

    else if (bad_count != 0 && right_count == 0) {
        printf("%s", badspeak_message);
        print_file("badfile.txt");
    }

    else if (bad_count == 0 && right_count != 0) {
        printf("%s", goodspeak_message);
        print_file("rightfile.txt");
    }
}

int main(int argc, char **argv) {

#if 0
    uint32_t height;
    uint32_t size;
    Node *root = bst_create();
    height = bst_height(root);
    size = bst_size(root);
    printf("height = %u   size = %u\n", height, size);
    bst_print(root);
    root = bst_insert(root, "mmmm", "new");
    bst_insert(root, "aaaa", "another1");
    bst_insert(root, "ooo", "cat");
    bst_insert(root, "pp", NULL);

    height = bst_height(root);
    size = bst_size(root);
    printf("height = %u   size = %u\n", height, size);
    bst_print(root);

    Node *find = bst_create();
    find = bst_find(root, "ooo");
    bst_print(find);

    return 0;
#endif

    int opt = 0;
    uint32_t ht_size = 1 << 16;
    uint32_t bf_size = 1 << 20;
    bool stat_flag = false;
    FILE *file;
    char old[MAXLEN];
    char new[MAXLEN];

    // Parses through command line arguments
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n  A word filtering program for the GPRSC.\n");
            printf("  Filters out and reports bad words parsed from stdin.\n\n");
            printf("USAGE\n  ./banhammer [-hs] [-t size] [-f size]\n\n");
            printf("OPTIONS\n");
            printf("  -h           Program usage and help.\n");
            printf("  -s           Print program statistics.\n");
            printf("  -t size      Specify hash table size (default: 10000).\n");
            printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
            break;
        case 's': stat_flag = true; break;
        case 't': ht_size = atoi(optarg); break;
        case 'f': bf_size = atoi(optarg); break;
        }
    }

    // Initializes bloom filter
    BloomFilter *bf = bf_create(bf_size);

    // Initializes hash table
    HashTable *ht = ht_create(ht_size);

    // Opens badspeak.txt
    file = fopen(BADSPEAK_FILE, "r");

    // Exits if unable to open badspeak.txt
    if (file == NULL) {
        printf("error file opening %s\n", BADSPEAK_FILE);
        return -1;
    }

    //int wordcount = 0;
    //printf("bf count %d\n", bf_count(bf));

    // Scans until end of badspeak.txt
    while (1) {
        //wordcount++;

        // Breaks if EOF reached
        int count = fscanf(file, "%s\n", old);
        if (count <= 0) {
            break;
        }

        //printf("%d %s\n", wordcount, word);

        // Inserts oldspeak into bloom filter and hash table
        bf_insert(bf, old);
        ht_insert(ht, old, NULL);
    }

#if 0
    //printf("bf count after %d\n", bf_count(bf));
    //test_bf(bf, "teresa");
    //test_bf(bf, "joseph");
    //test_bf(bf, "misleader");

    //bf_print(bf);
    //ht_print(ht);

    ht_insert(ht, "tj", "kkkk");
    Node *node = ht_lookup(ht, "tj");
    if (node == NULL) {
        printf("lookup failed\n");
    } else {
        printf("lookup success %s\n", node->oldspeak);
        printf("lookup success %s\n", node->newspeak);
    }
#endif

    // Closes badspeak.txt
    fclose(file);

    // Opens newspeak.txt
    file = fopen(NEWSPEAK_FILE, "r");

    // Exits if unable to open newspeak.txt
    if (file == NULL) {
        printf("error file opening %s\n", NEWSPEAK_FILE);
        return -1;
    }

    //wordcount = 0;

    // Scans until end of newspeak.txt
    while (1) {
        //wordcount++;

        // Breaks if EOF reached
        int count = fscanf(file, "%s %s\n", old, new); // scan badspeak
        if (count <= 0) {
            break;
        }

        //printf("%d %s %s\n", wordcount, old, new);

        // Inserts oldspeak into bloom filter
        bf_insert(bf, old);

        // Inserts oldspeak and newspeak into hash table
        ht_insert(ht, old, new);
    }

    // Closes newspeak.txt
    fclose(file);

    create_report(bf, ht);

#if 0

    regex_t re;

    if (regcomp(&re, WORD, REG_EXTENDED)){
    	printf("failed to compile\n");
	return -1;
    }

    create_report(bf, ht);

    char *word = NULL;

    while((word = next_word(stdin, &re)) != NULL){
	printf("word return %s\n", word);
    	if (bf_probe(bf, word) == false){
		continue;
	}
	Node *ht_node = ht_lookup(ht, word);
	if (ht_node == NULL){
		continue;
	}
	printf("found guilty\n");
	node_print(ht_node);

	if (ht_node->newspeak == NULL){
		printf("no newspeak\n");
	}
    }
#endif

    // Checks if -s was enabled
    if (stat_flag) {
        //calculate statistics and print
        printf("Average binary search tree size: %f\n", ht_avg_bst_size(ht));
        printf("Average binary search tree height: %f\n", ht_avg_bst_height(ht));
    }

    // Frees memory
    bf_delete(&bf);
    ht_delete(&ht);

    return 0;
}
