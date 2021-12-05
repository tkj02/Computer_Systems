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
#define WORD          "[a-zA-Z0-9\'_-]+"

// Opens, reads, and prints file content
// Used to print badspeak and/or old/newspeak in final message report
// Used in create_report()
void print_file(char *filename) {
    // Opens given file for reading
    FILE *fp = fopen(filename, "r");

    // If opening file failed, prints error and stops
    if (fp == NULL) {
        printf("error opening %s\n", filename);
        return;
    }

    // Creates buffer for calling fgets() later
    // (assumes max size of each line)
    char buffer[256];

    // Loops to print file content until EOF
    while (1) {
        // Stores read characters in buffer
        // Breaks at EOF
        if (fgets(buffer, 256, fp) == NULL) {
            break;
        }

        // Prints line contained in buffer
        printf("%s", buffer);
    }
    fclose(fp);
}

// Generates message report
// Uses parser module from assignment document
void create_report(BloomFilter *bf, HashTable *ht) {
    // Files for storing badspeak and old/newspeak respectively
    FILE *badfile;
    FILE *rightfile;

    // Initializes regex variable
    regex_t re;

    // Compiles using WORD definition
    // Stops if compilation failed
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        printf("failed to compile\n");
        return;
    }

    // Opens file for storing badspeak
    // Stops if opening failed
    badfile = fopen("badfile.txt", "w");
    if (badfile == NULL) {
        printf("error openining file badfile.txt\n");
        return;
    }

    // Opens file for storing oldspeak and newspeak
    // Stops if opening failed
    rightfile = fopen("rightfile.txt", "w");
    if (rightfile == NULL) {
        printf("error openining file rightfile.txt\n");
        return;
    }

    // Initializes variable for tracking number of badspeak
    int bad_count = 0;

    // Initializes variable for tracking number of old/newspeak
    int right_count = 0;

    // Creates variable to store characters (the word)
    char *word = NULL;

    // Loops while end of user statement not reached
    // Calls next_word() in parser.h to check each word
    while ((word = next_word(stdin, &re)) != NULL) {
        // Checks if word is in bloom filter
        // If word is not in bloom filter, continues looping
        if (bf_probe(bf, word) == false) {
            continue;
        }

        // Word is in bloom filter at this point
        // Checks if word is in hash table to confirm
        // Stores pointer of word or NULL in ht_node
        Node *ht_node = ht_lookup(ht, word);

        // If returned node is NULL, word is not in hash table
        // Indicates false positive from bloom filter and continues looping
        if (ht_node == NULL) {
            continue;
        }

        // Word is definitely a forbidden word at this point

        // Checks if word does not have a newspeak translation
        // If so, it is a badspeak word
        if (ht_node->newspeak == NULL) {
            // Increments badspeak counter by one
            bad_count++;

            // Stores oldspeak (forbidden word) into file of badspeak
            fprintf(badfile, "%s\n", ht_node->oldspeak);

            // Word must have a newspeak translation
        } else {
            // Increments rightspeak counter by one
            right_count++;

            // Stores oldspeak and newspeak into file of rightspeak
            fprintf(rightfile, "%s -> %s\n", ht_node->oldspeak, ht_node->newspeak);
        }
    }

    // Frees regex memory
    clear_words();
    regfree(&re);

    // Closes files (not needed anymore)
    fclose(badfile);
    fclose(rightfile);

    // User used both badspeak and old/newspeak
    if (bad_count != 0 && right_count != 0) {
        // Prints mispeak message from messages.h
        printf("%s", mixspeak_message);

        // Prints list of badspeak used
        print_file("badfile.txt");

        // Prints list of oldspeak used with newspeak translation
        print_file("rightfile.txt");
    }

    // User used only badspeak
    else if (bad_count != 0 && right_count == 0) {
        // Prints badspeak message from messages.h
        printf("%s", badspeak_message);

        // Prints list of badspeak used
        print_file("badfile.txt");
    }

    // User used only old/newspeak
    else if (bad_count == 0 && right_count != 0) {
        // Prints goodspeak message from messages.h
        printf("%s", goodspeak_message);

        // Prints list of oldspeak used with newspeak translation
        print_file("rightfile.txt");
    }
}

// Main function
int main(int argc, char **argv) {
    // Variable for parsing options
    int opt = 0;

    // Default hash table size
    uint32_t ht_size = 1 << 16;

    // Default bloom filter size
    uint32_t bf_size = 1 << 20;

    // Flag for statistics option
    bool stat_flag = false;

    // File pointer for opening files
    FILE *file;

    // Buffers to hold scanned old/newspeak
    char old[MAXLEN];
    char new[MAXLEN];

    // Parses through command line arguments
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {

        // Prints help message
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

        // Enables statistics printing option
        case 's': stat_flag = true; break;

        // Uses user hash table size
        case 't': ht_size = atoi(optarg); break;

        // Uses user bloom filter size
        case 'f': bf_size = atoi(optarg); break;
        }
    }

    // Initializes bloom filter
    BloomFilter *bf = bf_create(bf_size);

    // Initializes hash table
    HashTable *ht = ht_create(ht_size);

    // Opens badspeak.txt for reading
    file = fopen(BADSPEAK_FILE, "r");

    // Exits if unable to open badspeak.txt
    if (file == NULL) {
        printf("error file opening %s\n", BADSPEAK_FILE);
        return -1;
    }

    // Loops until end of badspeak.txt
    while (1) {
        // Breaks if EOF reached
        int count = fscanf(file, "%s\n", old);
        if (count <= 0) {
            break;
        }

        // Inserts oldspeak into bloom filter and hash table
        bf_insert(bf, old);
        ht_insert(ht, old, NULL);
    }

    // Closes badspeak.txt
    fclose(file);

    // Opens newspeak.txt
    file = fopen(NEWSPEAK_FILE, "r");

    // Exits if unable to open newspeak.txt
    if (file == NULL) {
        printf("error file opening %s\n", NEWSPEAK_FILE);
        return -1;
    }

    // Scans until end of newspeak.txt
    while (1) {
        // Breaks if EOF reached
        int count = fscanf(file, "%s %s\n", old, new);
        if (count <= 0) {
            break;
        }

        // Inserts oldspeak into bloom filter
        bf_insert(bf, old);

        // Inserts oldspeak and newspeak into hash table
        ht_insert(ht, old, new);
    }

    // Closes newspeak.txt
    fclose(file);

    // Calls function to create necessary message
    create_report(bf, ht);

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
