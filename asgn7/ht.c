#include "ht.h"
#include "salts.h"
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
        return NULL;
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

#if 0
uint32_t ht_size(HashTable *ht) {
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
}

uint32_t ht_count(HashTable *ht) {
}

double ht_avg_bst_size(HashTable *ht) {
}

double ht_avg_bst_height(HashTable *ht) {
}

void ht_print(HashTable *ht) {
}
#endif
