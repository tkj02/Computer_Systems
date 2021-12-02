#include "ht.h"
#include "salts.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>

// Creates hash table structure
struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

HashTable *ht_create(uint32_t size) {
    // Allocates memory for hash table
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht == NULL) {
        return ht;
    }

    // Sets salt values according to salts.h
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;

    // Sets hash table size to given size
    ht->size = size;

    // Allocates memory for trees
    ht->trees = (Node **) malloc(size * sizeof(Node *));

    return ht;
}

void ht_delete(HashTable **ht) {
    // Frees tree memory
    free((*ht)->trees);

    // Frees hash table memory
    free(*ht);
    *ht = NULL;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    // Gets bit from hashing
    uint32_t ht_bit = hash(ht->salt, oldspeak) % ht_size(ht);

    // Finds node in tree at specified bit
    return bst_find(ht->trees[ht_bit], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    // Gets bit from hashing
    uint32_t ht_bit = hash(ht->salt, oldspeak) % ht_size(ht);

    // Inserts oldspeak in tree at specified bit
    bst_insert(ht->trees[ht_bit], oldspeak, newspeak);
}

uint32_t ht_count(HashTable *ht) {
    // Keeps track of number of non-NULL trees
    uint32_t counter = 0;

    // Iterates through all indices of tree
    for (uint32_t i = 0; i < ht->size; i++) {
        // Checks if height is is zero (meaning bst is NULL)
        if (bst_height(ht->trees[i]) == 0) {
            continue;
        }
        // Increments counter if tree at index is non-NULL
        counter++;
    }
    return counter;
}

double ht_avg_bst_size(HashTable *ht) {
    // Creates counter to keep track of bst size
    uint32_t bst_counter = 0;

    // Number of non-NULL bsts in hash table
    uint32_t ht_counter = ht_count(ht);

    // Iterates through all indices of tree
    for (uint32_t i = 0; i < ht->size; i++) {
        // Increments bst size counter
        bst_counter += bst_size(ht->trees[i]);
    }

    // Returns average bst size
    return bst_counter / ht_counter;
}

double ht_avg_bst_height(HashTable *ht) {
    // Creates counter to keep track of bst height
    uint32_t bst_counter = 0;

    // Number of non-NULL bsts in hash table
    uint32_t ht_counter = ht_count(ht);

    // Iterates through all indices of tree
    for (uint32_t i = 0; i < ht->size; i++) {
        // Increments bst height counter
        bst_counter += bst_height(ht->trees[i]);
    }

    // Returns average bst height
    return bst_counter / ht_counter;
}

void ht_print(HashTable *ht) {
    // Iterates through all indices of tree
    for (uint32_t i = 0; i < ht->size; i++) {
        // Prints bst at index of hash table
        bst_print(ht->trees[i]);
        printf("\n");
    }
}
