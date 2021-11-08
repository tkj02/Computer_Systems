#include "defines.h"
#include "stack.h"
#include "pq.h"
#include "node.h"
#include "code.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

bool read_bit(int infile, uint8_t *bit);

// Builds Huffman tree
// Dequeues children and joins to make parent
// Dequeues remaining node for root
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
int recur_count1 = 0;
int tree_depth = 0;

void building_codes(Node *root, Code table[static ALPHABET], Code *c) {
    uint8_t popped_bit;
    tree_depth++;
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL) {
        table[root->symbol] = *c;
        recur_count1++;
        tree_depth--;
        return;
    }
    code_push_bit(c, 0);
    if (root->left == NULL) {
        printf("Left = NULL  0x%02x Count: %d Depth:%d \n", root->symbol, recur_count1, tree_depth);
    }
    if (root->right == NULL) {
        printf(
            "Rightt = NULL  0x%02x Count: %d Depth:%d \n", root->symbol, recur_count1, tree_depth);
    }
    building_codes(root->left, table, c);
    code_pop_bit(c, &popped_bit);
    code_push_bit(c, 1);
    building_codes(root->right, table, c);
    code_pop_bit(c, &popped_bit);
    tree_depth--;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    building_codes(root, table, &c);
}

void dump_tree(int outfile, Node *root) {
    if (root == NULL) {
        return;
    }
    dump_tree(outfile, root->left);
    dump_tree(outfile, root->right);
    uint8_t ch[2];
    if (root->left == NULL && root->right == NULL) {
        ch[0] = 'L';
        ch[1] = root->symbol;
        write_bytes(outfile, ch, 2);
    } else {
        ch[0] = 'I';
        write_bytes(outfile, ch, 1);
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *stack = stack_create(32);
    for (int i = 0; i < nbytes; i++) {

        if (tree[i] == 'L') {
            Node *n = node_create(tree[i + 1], 0);
            stack_push(stack, n);
            i++;
        } else {
            if (tree[i] == 'I') {
                Node *left;
                Node *right;
                stack_pop(stack, &right);
                stack_pop(stack, &left);
                Node *parent = node_join(left, right);
                stack_push(stack, parent);
            }
        }
    }
    Node *root;
    stack_pop(stack, &root);
    stack_delete(&stack);
    return root;
}

void delete_tree(Node **root) {
    if (*root == NULL) {
        return;
    }
    delete_tree(&(*root)->left);
    delete_tree(&(*root)->right);
    node_delete(root);
    *root = NULL;
}
