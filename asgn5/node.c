#include "node.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    Node *left;
    Node *right;
    uint8_t symbol;
    uint64_t frequency;
};

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

void node_delete(Node **n) {
    void free(void *n);
    *n = NULL;
}

Node *node_join(Node *left, Node *right) {
    left->frequency = left_freq;
    right->frequency = right_freq;
    Node *new_node = node_create('$', left_freq + right_freq);
    return new_node;
}

void node_print(Node *n) {
    printf("node symbol: %d", n->symbol);
    printf("node freq: %lu", n->frequency);
    if (n->left != NULL && n->right != NULL) {
        n->left = left;
        n->right = right;
        printf("node's left symbol: %d", left->symbol);
        printf("node's right symbol: %d", right->symbol);
        printf("node's left freq: %lu", left->frequency);
        printf("node's right freq: %lu", right->frequency);
    }
}
