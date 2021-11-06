#include "defines.h"
#include "pq.h"
#include "node.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {
    bool return_stat;
    PriorityQueue *pq = pq_create(ALPHABET);
    if (pq == NULL) {
        printf("pq failed\n");
        return NULL;
    }
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] == 0) {
            continue;
        }
        Node *node = node_create(i, hist[i]);
        enqueue(pq, node);
    }
    while (pq_size(pq) >= 2) {
        Node *nl, *nr, *np;
        return_stat = dequeue(pq, &nl);
        if (return_stat == false) {
            printf("error dequeueing left\n");
            pq_delete(&pq);
            return NULL;
        }
        return_stat = dequeue(pq, &nr);
        if (return_stat == false) {
            printf("error dequeueing right\n");
            pq_delete(&pq);
            return NULL;
        }
        np = node_join(nl, nr);
        if (np == NULL) {
            printf("error joining\n");
            pq_delete(&pq);
            return NULL;
        }
        enqueue(pq, np);
    }
    if (pq_size(pq) == 1) {
        Node *root;
        return_stat = dequeue(pq, &root);
        if (return_stat == false) {
            printf("error dequeueing root\n");
            pq_delete(&pq);
            return NULL;
        }
        return root;
    } else {
        printf("error q count isn't 1 for root\n");
    }
    return NULL;
}

void building_codes(Node *root, Code table[static ALPHABET], Code *c) {
    uint8_t popped_bit;
    if (root->symbol != '$') {
        table[root->symbol] = *c;
        return;
    }
    code_push_bit(c, 0);
    building_codes(root->left, table, c);
    code_pop_bit(c, &popped_bit);
    code_push_bit(c, 1);
    building_codes(root->right, table, c);
    code_pop_bit(c, &popped_bit);
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    building_codes(root, table, &c);
}

#if 0
void dump_tree(int outfile, Node *root) {
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
}

void delete_tree(Node **root) {
}
#endif
