#include "node.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Using Node struct from node.h
// Has Node *left, Node *right, uint8_t symbol, and uint64_t frequency

// Creates node
// Children are set to null
// Symbol and freq are initialized
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->left = NULL;
        n->right = NULL;
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

// Frees memory and sets pointer to null
void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
}

// Creates a parent node
// Symbol is $ and freq is its childrens' freq
Node *node_join(Node *left, Node *right) {
    Node *new_node = node_create('$', left->frequency + right->frequency);
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

// Prints node symbol and freq
// If children exist, prints their data too
void node_print(Node *n) {
    printf("node symbol: %d", n->symbol);
    printf("node freq: %lu", n->frequency);
    if (n->left != NULL && n->right != NULL) {
        printf("node's left symbol: %d", n->left->symbol);
        printf("node's right symbol: %d", n->right->symbol);
        printf("node's left freq: %lu", n->left->frequency);
        printf("node's right freq: %lu", n->right->frequency);
    }
}
