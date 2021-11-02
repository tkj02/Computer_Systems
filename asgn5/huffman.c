#include "node.h"
#include "code.h"
#include "defines.h"
#include <stdint.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {
    pq = node_create(symbol, 255);
    while (pq->size > 1) {
        pq->left = dequeue(pq, pq->left);
        pq->right = dequeue(pq, pq->right);
        Node *parent = node_join(pq->left, pq->right);
        enqueue(pq, parent);
        --pq->size;
    }
    Node *root = dequeue(pq, __);
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
}

void dump_tree(int outfile, Node *root) {
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
}

void delete_tree(Node **root) {
}
